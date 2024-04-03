// Copyright Epic Games, Inc. All Rights Reserved.

#include "PrototypeCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Net/UnrealNetwork.h"
#include "Tutorial/ThirdPersonProjectile.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// APrototypeCharacter

APrototypeCharacter::APrototypeCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Initialize health values
	MaxHealth = 100.0f;
	CurrentHealth = MaxHealth;

	// Initialize projectile class
	ProjectileClass = AThirdPersonProjectile::StaticClass();

	// Initialize fire rate
	FireRate = 0.25f;
	bIsFiringWeapon = false;
	
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void APrototypeCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APrototypeCharacter, CurrentHealth);
}

void APrototypeCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void APrototypeCharacter::SetCurrentHealth(float HealthValue)
{
	if(GetLocalRole() == ROLE_Authority)
	{
		CurrentHealth = FMath::Clamp(HealthValue, 0.0f, MaxHealth);
		OnHealthUpdate();
	}
}

float APrototypeCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	const float DamageApplied = CurrentHealth - DamageAmount;
	SetCurrentHealth(DamageApplied);
	return DamageApplied;
}

//////////////////////////////////////////////////////////////////////////
// Input

void APrototypeCharacter::OnRep_CurrentHealth()
{
	OnHealthUpdate();
}

void APrototypeCharacter::OnHealthUpdate()
{
	// Client side logic
	if(IsLocallyControlled() && GetLocalRole() == ROLE_SimulatedProxy)
	{
		const FString HealthMessage = FString::Printf(TEXT("You now have %f health."), CurrentHealth);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, HealthMessage);

		if(CurrentHealth<=0)
		{
			const FString DeathMessage = FString::Printf(TEXT("You have been killed."));
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, DeathMessage);
		}
	}

	// Server side logic
	if(GetLocalRole() == ROLE_Authority)
	{
		const FString HealthMessage = FString::Printf(TEXT("%s now has %f health."), *GetNameSafe(this), CurrentHealth);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, HealthMessage);
		if(CurrentHealth<=0)
		{
			const FString DeathMessage = FString::Printf(TEXT("%s have been killed."), *GetNameSafe(this));
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, DeathMessage);
		}
	}
}


void APrototypeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Firing
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &APrototypeCharacter::StartFire);
		// EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &APrototypeCharacter::StartFire);
		// EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Ongoing, this, &APrototypeCharacter::StartFire);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Canceled, this, &APrototypeCharacter::StopFire);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Completed, this, &APrototypeCharacter::StopFire);
		
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APrototypeCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APrototypeCharacter::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void APrototypeCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APrototypeCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APrototypeCharacter::StartFire()
{
	if(!bIsFiringWeapon)
	{
		// Set is firing weapon is true
		bIsFiringWeapon = true;

		// Set timer based on the fire rate
		UWorld* World = GetWorld();
		World->GetTimerManager().SetTimer(FiringTimer,
			this,
			&APrototypeCharacter::StartFire,
			FireRate,
			false);
		HandleFire();
	}
		
}

void APrototypeCharacter::StopFire()
{
		// Get time to check if firing weapon is stopped
		UWorld* World = GetWorld();
		const float RemainingTime = World->GetTimerManager().GetTimerRemaining(FiringTimer);
	
		if(RemainingTime <= 0.0f)
		{
			FString StopMessage = FString::Printf(TEXT("%s stops firing projectile!"), *GetNameSafe(this));
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, StopMessage);

			bIsFiringWeapon = false;
		}
}

void APrototypeCharacter::HandleFire_Implementation()
{
	if(GetLocalRole() == ROLE_Authority)
	{
		FString FiringMessage = FString::Printf(TEXT("%s is firing projectile!"), *GetNameSafe(this));
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, FiringMessage);
		
		const FVector SpawnLocation = GetActorLocation() + GetActorRotation().Vector() * 100.0f + GetActorUpVector() * 50.0f;
		const FRotator SpawnRotation = GetActorRotation();

		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Instigator = GetInstigator();
		SpawnParameters.Owner = this;

		const AThirdPersonProjectile* SpawnProjectile =
			GetWorld()->SpawnActor<AThirdPersonProjectile>(SpawnLocation, SpawnRotation, SpawnParameters);
	}
	
}
 
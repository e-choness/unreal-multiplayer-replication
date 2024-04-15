// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/SDCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameMode/SDCharacterStats.h"
#include "Engine/DataTable.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ASDCharacter::ASDCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create spring arm for camera to attach to
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 800.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera and attach it to the spring arm
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCapsuleComponent()->InitCapsuleSize(60.0f, 96.0f);

	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -91.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshAsset(TEXT("/Game/KayKit/Characters/rogue"));
	if(SkeletalMeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SkeletalMeshAsset.Object);
	}

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;

	// Set character replicates to true
	bReplicates = true;

}

// Called when the game starts or when spawned
void ASDCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Add input mapping context
	if(APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if(UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			SubSystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	// Start the character with level 1 stats
	UpdateCharacterStats(1);

	// Update character walk speed
	if(GetCharacterStats())
	{
		GetCharacterMovement()->MaxWalkSpeed = GetCharacterStats()->WalkSpeed;
	}
	
}

void ASDCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASDCharacter, Score)
}

void ASDCharacter::Move(const FInputActionValue& Value)
{
	if(Controller == nullptr) return;
	
	const auto MoveValue = Value.Get<FVector2D>();

	const auto Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	const auto ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const auto RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MoveValue.Y);
	AddMovementInput(RightDirection, MoveValue.X);
}

void ASDCharacter::Look(const FInputActionValue& Value)
{
	if(Controller == nullptr) return;
	
	const auto LookValue = Value.Get<FVector2D>();

	AddControllerYawInput(LookValue.X);
	AddControllerPitchInput(LookValue.Y);
}

void ASDCharacter::SprintStart(const FInputActionValue& Value)
{
	if(GetCharacterStats())
	{
		GetCharacterMovement()->MaxWalkSpeed = GetCharacterStats()->SprintSpeed;
	}
}

void ASDCharacter::SprintEnd(const FInputActionValue& Value)
{
	if(GetCharacterStats())
	{
		GetCharacterMovement()->MaxWalkSpeed = GetCharacterStats()->WalkSpeed;
	}
}

void ASDCharacter::Interact(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(3, 5.0f, FColor::Purple, TEXT("Interact"));
}

void ASDCharacter::UpdateCharacterStats(int32 CharacterLevel)
{
	if(CharacterDataTable)
	{
		TArray<FSDCharacterStats*> CharacterStatesRows;
		CharacterDataTable->GetAllRows<FSDCharacterStats>(TEXT("SDCharacter"), CharacterStatesRows);
		if(CharacterStatesRows.Num() > 0)
		{
			const auto NewCharacterLevel = FMath::Clamp(CharacterLevel, 1, CharacterStatesRows.Num());
			CharacterStats = CharacterStatesRows[NewCharacterLevel - 1];

			GetCharacterMovement()->MaxWalkSpeed = GetCharacterStats()->WalkSpeed;
		}
	}
}

void ASDCharacter::OnRep_Score()
{
}

// Called every frame

void ASDCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input

void ASDCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Bind Move Action
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASDCharacter::Move);

		//Bind Look Action
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASDCharacter::Look);

		// Bind Sprint Action
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &ASDCharacter::SprintStart);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ASDCharacter::SprintEnd);

		// Bind Interact Action
		EnhancedInputComponent->BindAction(InteractActin, ETriggerEvent::Started, this, &ASDCharacter::Interact);
	}
}
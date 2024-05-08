// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/SDWeaponProjectileComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameMode/SDWeaponProjectileBase.h"
#include "GameMode/SDCharacter.h"

// Sets default values for this component's properties
USDWeaponProjectileComponent::USDWeaponProjectileComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	ProjectileClass = ASDWeaponProjectileBase::StaticClass();
}

void USDWeaponProjectileComponent::SetProjectileClass(TSubclassOf<ASDWeaponProjectileBase> NewProjectileClass)
{
	ProjectileClass = NewProjectileClass;
}


// Called when the game starts
void USDWeaponProjectileComponent::BeginPlay()
{
	Super::BeginPlay();

	// Add input action based on the weapon we are using, avoid clutter inputs to the player character
	const ACharacter* Character = Cast<ACharacter>(GetOwner());
	if(!Character) return;

	if(const APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(WeaponMappingContext, 1);
		}

		if(UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			EnhancedInputComponent->BindAction(ThrowAction, ETriggerEvent::Triggered, this, &USDWeaponProjectileComponent::Throw);
		}
	}
}

void USDWeaponProjectileComponent::Throw()
{
	Throw_Server();
}

void USDWeaponProjectileComponent::PlayThrowAnimation() const
{
	const auto Character = Cast<ASDCharacter>(GetOwner());

	if(ThrowAnimation != nullptr)
	{
		if(const auto AnimInstance = Character->GetMesh()->GetAnimInstance(); AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(ThrowAnimation, 1.0f);
		}
	}
}

void USDWeaponProjectileComponent::SpawnProjectile() const
{
	const auto Character = Cast<ASDCharacter>(GetOwner());
	const auto ProjectileSpawnLocation = GetComponentLocation();
	const auto ProjectileSpawnRotation = GetComponentRotation();
	
	auto ProjectileParams = FActorSpawnParameters();
	ProjectileParams.Owner = GetOwner();
	ProjectileParams.Instigator = Character;

	GetWorld()->SpawnActor<ASDWeaponProjectileBase>(ProjectileClass, ProjectileSpawnLocation, ProjectileSpawnRotation, ProjectileParams);
}

void USDWeaponProjectileComponent::Throw_Server_Implementation()
{
	if(!ProjectileClass) return;
	Throw_Client();
	
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &USDWeaponProjectileComponent::SpawnProjectile, 0.4f, false);
}


void USDWeaponProjectileComponent::Throw_Client_Implementation()
{
	PlayThrowAnimation();
}

// Called every frame
void USDWeaponProjectileComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


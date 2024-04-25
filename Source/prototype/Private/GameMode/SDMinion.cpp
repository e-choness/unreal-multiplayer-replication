// Fill out your copyright notice in the Description page of Project Settings.

#include "AIController.h"
#include "NavigationSystem.h"
#include "GameMode/SDCharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "Components/SphereComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameMode/SDMinion.h"

// Sets default values
ASDMinion::ASDMinion()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	
	bReplicates = true;
}

void ASDMinion::SetNextPatrolLocation()
{
}

void ASDMinion::Chase(APawn* Pawn)
{
}

void ASDMinion::OnPawnDetected(APawn* Pawn)
{
}

void ASDMinion::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
}

void ASDMinion::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

// Called when the game starts or when spawned
void ASDMinion::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASDMinion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASDMinion::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


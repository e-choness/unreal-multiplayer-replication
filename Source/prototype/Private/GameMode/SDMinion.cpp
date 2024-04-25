// Fill out your copyright notice in the Description page of Project Settings.

#include "GameMode/SDMinion.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "GameMode/SDCharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "Components/SphereComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ASDMinion::ASDMinion()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Disable controller pitch, roll and yaw
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	// Allow AI controller to poss the 
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AAIController::StaticClass();

	PawnSense = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSense"));
	PawnSense->SensingInterval = 0.8f;
	PawnSense->SetPeripheralVisionAngle(45.0f);
	PawnSense->SightRadius = 1500.0f;
	PawnSense->LOSHearingThreshold = 800.0f;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetSphereRadius(100.0f);
	Collision->SetupAttachment(RootComponent);

	GetCapsuleComponent()->InitCapsuleSize(60.0f, 96.0f);
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);

	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -91.0f));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMesh(TEXT("/Game/KayKit/Skeletons/skeleton_minion"));

	if(SkeletalMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SkeletalMesh.Object);
	}

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 200.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;
	
	bReplicates = true;
}

void ASDMinion::SetNextPatrolLocation()
{
	if(GetLocalRole() != ROLE_Authority) return;

	GetCharacterMovement()->MaxWalkSpeed = MinionStats.PatrolSpeed;
	
	const auto LocationFound = UNavigationSystemV1::K2_GetRandomPointInNavigableRadius(this, GetActorLocation(), PatrolLocation, MinionStats.PatrolRadius);

	if(LocationFound)
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), PatrolLocation);
	}
}

bool ASDMinion::IsChasing() const
{
	return GetMovementComponent()->GetMaxSpeed() == MinionStats.ChaseSpeed;
}

void ASDMinion::Chase(APawn* Pawn)
{
	if(GetLocalRole()!=ROLE_Authority) return;
	
	GetCharacterMovement()->MaxWalkSpeed = MinionStats.ChaseSpeed;
	UAIBlueprintHelperLibrary::SimpleMoveToActor(GetController(), Pawn);
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Black, FString::Printf(TEXT("The minion chases the player at speed %f."), GetCharacterMovement()->MaxWalkSpeed));
}

void ASDMinion::OnPawnDetected(APawn* Pawn)
{
	if(!Pawn->IsA<ASDCharacter>()) return;
	GEngine->AddOnScreenDebugMessage(3, 3.0f, FColor::Red, TEXT("The minion sees the player."));
	
	if(GetMovementComponent()->GetMaxSpeed() != MinionStats.ChaseSpeed)
	{
		Chase(Pawn);
	}
}

void ASDMinion::OnHearNoises(APawn* Pawn)
{
	if(!Pawn->IsA<ASDCharacter>()) return;
	GEngine->AddOnScreenDebugMessage(3, 3.0f, FColor::Yellow, TEXT("The minion hears the player."));
}

void ASDMinion::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!OtherActor->IsA<ASDCharacter>()) return;
	GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Orange, TEXT("The minion senses the player."));
}

void ASDMinion::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if(GetLocalRole() != ROLE_Authority) return;

	OnActorBeginOverlap.AddDynamic(this, &ASDMinion::OnBeginOverlap);
	GetPawnSense()->OnSeePawn.AddDynamic(this, &ASDMinion::OnPawnDetected);
	// GetPawnSense()->OnHearNoise.AddDynamic(this, &ASDMinion::OnHearNoises);
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

	if(GetLocalRole() != ROLE_Authority) return;
	
	if(IsChasing()) return;

	if((GetActorLocation() - PatrolLocation).Size() < 500.0f)
	{
		SetNextPatrolLocation();
	}
}

// Called to bind functionality to input
void ASDMinion::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


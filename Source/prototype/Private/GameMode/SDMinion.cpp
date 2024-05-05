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
#include "GameMode/SDGameMode.h"

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
	
	IsRestartPatrolling = false;
	
	bReplicates = true;
}

void ASDMinion::SetNextPatrolLocation()
{
	if(GetLocalRole() != ROLE_Authority) return;

	GetCharacterMovement()->MaxWalkSpeed = MinionStats.PatrolSpeed;
	
	if(NavigationSystemV1->GetRandomPointInNavigableRadius(GetActorLocation(),MinionStats.PatrolRadius, PatrolLocation))
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), PatrolLocation);
	}

	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Cyan, FString::Printf(TEXT("The minion is patrolling to %f %f %f."), PatrolLocation.Location.X, PatrolLocation.Location.Y, PatrolLocation.Location.Z));
}

void ASDMinion::RestartPatrol()
{
	const auto RemainingTime = GetWorldTimerManager().GetTimerRemaining(PatrolTimer);
	
	GEngine->AddOnScreenDebugMessage(3, 5.0f, FColor::Blue, FString::Printf(TEXT("Remaining patrol time: %f"), RemainingTime));
	if(RemainingTime <= 0.0f)
	{
		GEngine->AddOnScreenDebugMessage(3, 5.0f, FColor::Blue, FString::Printf(TEXT("Restart patrolling.")));
		SetNextPatrolLocation();
		IsRestartPatrolling = false;
	}
}

bool ASDMinion::IsChasing() const
{
	return GetMovementComponent()->GetMaxSpeed() == MinionStats.ChaseSpeed;
}

bool ASDMinion::IsMoving() const
{
	return GetCharacterMovement()->Velocity.Length() > 0.0f;
}

void ASDMinion::Chase(APawn* Pawn)
{
	if(GetLocalRole()!=ROLE_Authority) return;
	
	GetCharacterMovement()->MaxWalkSpeed = MinionStats.ChaseSpeed;
	UAIBlueprintHelperLibrary::SimpleMoveToActor(GetController(), Pawn);

	if(const auto GameMode = Cast<ASDGameMode>(GetWorld()->GetAuthGameMode()))
	{
		GameMode->AlertMinions(this, Pawn->GetActorLocation(), MinionStats.AlertRadius);
	}
	
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Black, FString::Printf(TEXT("The minion chases the player at speed %f."), GetCharacterMovement()->MaxWalkSpeed));
}

void ASDMinion::OnPawnDetected(APawn* Pawn)
{
	if(!Pawn->IsA<ASDCharacter>()) return;
	GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Red, TEXT("The minion sees the player."));
	GEngine->AddOnScreenDebugMessage(2, 5.0f, FColor::Red, FString::Printf(TEXT("The minion moving speed is %f."), GetCharacterMovement()->GetMaxSpeed()));
	GEngine->AddOnScreenDebugMessage(3, 5.0f, FColor::Red, FString::Printf(TEXT("The minion velocity is %f %f %f."), GetCharacterMovement()->GetLastUpdateVelocity().X, GetCharacterMovement()->GetLastUpdateVelocity().Y, GetCharacterMovement()->GetLastUpdateVelocity().Z));
	
	if(!IsChasing())
	{
		Chase(Pawn);
	}
}

void ASDMinion::OnHearNoises(APawn* PawnInstigator, const FVector& Location, float Volume)
{
	if(!PawnInstigator->IsA<ASDCharacter>()) return;
	GEngine->AddOnScreenDebugMessage(3, 3.0f, FColor::Yellow, TEXT("The minion hears the player."));
	GoToLocation(Location);
}

void ASDMinion::OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if(!OtherActor->IsA<ASDCharacter>()) return;
	GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Orange, TEXT("The minion senses the player."));
}

void ASDMinion::GoToLocation(const FVector& Location)
{
	PatrolLocation.Location = Location;
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), PatrolLocation.Location);
}

void ASDMinion::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if(GetLocalRole() != ROLE_Authority) return;

	OnActorBeginOverlap.AddDynamic(this, &ASDMinion::OnBeginOverlap);
	GetPawnSense()->OnSeePawn.AddDynamic(this, &ASDMinion::OnPawnDetected);
	GetPawnSense()->OnHearNoise.AddDynamic(this, &ASDMinion::OnHearNoises);
	NavigationSystemV1 = Cast<UNavigationSystemV1>(GetWorld()->GetNavigationSystem());
}

// Called when the game starts or when spawned
void ASDMinion::BeginPlay()
{
	Super::BeginPlay();
	SetNextPatrolLocation();
}

// Called every frame
void ASDMinion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(GetLocalRole() != ROLE_Authority) return;

	if(IsRestartPatrolling) return;

	if(!IsMoving())
	{
		GEngine->AddOnScreenDebugMessage(1, 3.0f, FColor::Red, TEXT("The minion stays still."));
		IsRestartPatrolling = true;
		GetWorldTimerManager().SetTimer(PatrolTimer, this, &ASDMinion::RestartPatrol, MinionStats.PatrolRestartTime, false);
	}
	
	if(IsChasing()) return;
	
	if((GetActorLocation() - PatrolLocation).Size() < MinionStats.PatrolThreshold)
	{
		SetNextPatrolLocation();
	}
}

// Called to bind functionality to input
void ASDMinion::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


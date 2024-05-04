// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/SDMinionSpawner.h"
#include "GameMode/SDMinion.h"
#include "Components/BoxComponent.h"

// Sets default values
ASDMinionSpawner::ASDMinionSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawn Area"));
	SpawnArea->SetupAttachment(RootComponent);
	SpawnArea->SetBoxExtent(FVector(1000.0f, 1000.0f, 100.0f));

	bReplicates = true;
}

// Called when the game starts or when spawned
void ASDMinionSpawner::BeginPlay()
{
	Super::BeginPlay();

	if(SpawnableMinions.IsEmpty()) return;

	if(GetLocalRole() != ROLE_Authority) return;

	for(int32 i=0; i<MinionsAtStart; i++)
	{
		Spawn();
	}

	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ASDMinionSpawner::Spawn, SpawnDelay, true, SpawnDelay);
}

void ASDMinionSpawner::Spawn()
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;

	const auto Minion = SpawnableMinions[FMath::RandRange(0, SpawnableMinions.Num()-1)];

	const auto Rotation = FRotator(0.0f, FMath::RandRange(0.0f, 360.0f), 0.0f);
	
	const auto SpawnX = SpawnArea->GetComponentLocation().X;
	const auto SpawnY = SpawnArea->GetComponentLocation().Y;
	const auto Location = SpawnArea->GetComponentLocation() + FVector(FMath::RandRange(-SpawnX, SpawnX), FMath::RandRange(-SpawnY, SpawnY), 0.0f);

	GetWorld()->SpawnActor<ASDMinion>(Minion, Location, Rotation, SpawnParameters);
}

// Called every frame
void ASDMinionSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


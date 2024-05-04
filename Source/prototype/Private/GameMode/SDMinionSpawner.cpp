// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/SDMinionSpawner.h"

// Sets default values
ASDMinionSpawner::ASDMinionSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASDMinionSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASDMinionSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


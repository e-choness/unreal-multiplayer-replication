// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/SDCharacter.h"

// Sets default values
ASDCharacter::ASDCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASDCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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

}


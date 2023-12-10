// Fill out your copyright notice in the Description page of Project Settings.

#include "IntroProject/Public/Follower.h"

// Sets default values
AFollower::AFollower()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create components
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	//  Setup camera
	Camera->FieldOfView = 120.f;
	Camera->SetRelativeLocation(FVector(100.0f, 0.0f, 50.0f));
}

// Called when the game starts or when spawned
void AFollower::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFollower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFollower::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/SDMainMenuPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"

// Sets default values
ASDMainMenuPawn::ASDMainMenuPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	RootComponent = Arrow;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->SetRelativeLocation(FVector(450.0f, 90.0f, 160.0f));
	Camera->SetRelativeRotation(FRotator(-10.0f, 180.0f, 0.0f));

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Camera->SetRelativeLocation(FVector(0.0f, -30.0f, 90.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshAsset(TEXT("/Game/KayKit/Characters/rogue"));
	if(SkeletalMeshAsset.Succeeded())
	{
		Mesh->SetSkeletalMesh(SkeletalMeshAsset.Object);
	}
}

// Called when the game starts or when spawned
void ASDMainMenuPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASDMainMenuPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASDMainMenuPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


// Fill out your copyright notice in the Description page of Project Settings.


#include "Tutorial/FloatingActor.h"

// Sets default values
AFloatingActor::AFloatingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize Static Mesh Component
	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	VisualMesh->SetupAttachment(RootComponent); // Attach the Static Mesh Component to the root actor, aka Floating Actor
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));

	if(CubeVisualAsset.Succeeded())
	{
		VisualMesh->SetStaticMesh(CubeVisualAsset.Object);
		VisualMesh->SetRelativeLocation(FVector::Zero());
	}
}

// Called when the game starts or when spawned
void AFloatingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFloatingActor::Tick(float DeltaTime)
{
	// Call Super::Tick
	Super::Tick(DeltaTime);

	// Get Floating Actor's transform information from previous frame
	FVector NewLocation = GetActorLocation();
	FRotator NewRotation = GetActorRotation();

	// Get game running time
	float RunningTime = GetGameTimeSinceCreation();

	// Calculate delta height
	float deltaHeight = FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime);

	// Apply delta height and rotation to transform from previous frame
	NewLocation.Z += deltaHeight * FloatScalar;
	NewRotation.Yaw += DeltaTime * RotationSpeed;

	SetActorLocationAndRotation(NewLocation,NewRotation);
}


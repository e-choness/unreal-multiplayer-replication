// Fill out your copyright notice in the Description page of Project Settings.


#include "Tutorial/FloatingActor.h"

#include "Net/UnrealNetwork.h"

// Sets default values
AFloatingActor::AFloatingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize Static Mesh Component
	OurVisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	OurVisualMesh->SetupAttachment(RootComponent); // Attach the Static Mesh Component to the root actor, aka Floating Actor
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));

	if(CubeVisualAsset.Succeeded())
	{
		OurVisualMesh->SetStaticMesh(CubeVisualAsset.Object);
		OurVisualMesh->SetRelativeLocation(FVector::Zero());
	}

	// Set the object to be replicable
	bReplicates = true;
}

void AFloatingActor::SetDomainEnter(const bool bToggle)
{
	if(bToggle != bIsEntered)
	{
		bIsEntered = bToggle;
		OnEnterDomainChanged(false);
	}
}

// Called when the game starts or when spawned
void AFloatingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFloatingActor::OnEnterDomainChanged(const bool bSkipAnimation)
{
	if(bIsEntered)
	{
		OnDomainEnter(bSkipAnimation);
	}else
	{
		OnDomainExit(bSkipAnimation);
	}
}

void AFloatingActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Set bIsEntered replication lifetime
	DOREPLIFETIME(AFloatingActor, bIsEntered);
}

void AFloatingActor::OnRep_bIsEntered()
{
	OnEnterDomainChanged(false);
}

// Called every frame
void AFloatingActor::Tick(const float DeltaTime)
{
	// Call Super::Tick
	Super::Tick(DeltaTime);

	// Get Floating Actor's transform information from previous frame
	FVector NewLocation = GetActorLocation();
	FRotator NewRotation = GetActorRotation();

	// Get game running time
	const float RunningTime = GetGameTimeSinceCreation();

	// Calculate delta height
	const float DeltaHeight = FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime);

	// Apply delta height and rotation to transform from previous frame
	NewLocation.Z += DeltaHeight * FloatScalar;
	NewRotation.Yaw += DeltaTime * RotationSpeed;

	SetActorLocationAndRotation(NewLocation,NewRotation);
}


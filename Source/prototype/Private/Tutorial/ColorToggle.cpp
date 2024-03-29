// Fill out your copyright notice in the Description page of Project Settings.


#include "Tutorial/ColorToggle.h"
#include "Net/UnrealNetwork.h"
#include "Components/SphereComponent.h"

// Sets default values
AColorToggle::AColorToggle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set object replicate state
	bReplicates = true;

	// Definition for the sphere component that will serve as the Root Component
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	SphereComponent->InitSphereRadius(50.0f);
	SphereComponent->SetCollisionProfileName(TEXT("ChangeColor"));
	RootComponent = SphereComponent;
	
	// Definition for the static mesh component for changing color
	static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultMesh(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);
	
	if(DefaultMesh.Succeeded())
	{
		StaticMesh->SetStaticMesh(DefaultMesh.Object);
		StaticMesh->SetRelativeLocation(FVector::Zero());
	}
	// ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultMesh(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	//
	// if(DefaultMesh.Succeeded())
	// {
	// 	StaticMeshComponent->SetStaticMesh(DefaultMesh.Object);
	// 	StaticMeshComponent->SetRelativeLocation(FVector::Zero());
	// }
}

void AColorToggle::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AColorToggle, CurrentColor);
}

// Called when the game starts or when spawned
void AColorToggle::BeginPlay()
{
	Super::BeginPlay();
	
}

void AColorToggle::OnEnterCollider()
{
	OnRep_CurrentColor();
	
}

void AColorToggle::OnRep_CurrentColor()
{
	if(GetLocalRole() == ROLE_Authority)
	{
		CurrentColor.R = FMath::FRandRange(0.0f, 1.0f);
		CurrentColor.G = FMath::FRandRange(0.0f, 1.0f);
		CurrentColor.B = FMath::FRandRange(0.0f, 1.0f);
	}
}

// Called every frame
void AColorToggle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


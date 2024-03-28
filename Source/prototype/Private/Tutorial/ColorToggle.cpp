// Fill out your copyright notice in the Description page of Project Settings.


#include "Tutorial/ColorToggle.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SphereComponent.h"
#include "Util/ColorConstants.h"

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
	ConstructorHelpers::FObjectFinder<UStaticMeshComponent> DefaultMesh(TEXT(""));
}

// Called when the game starts or when spawned
void AColorToggle::BeginPlay()
{
	Super::BeginPlay();
	
}

void AColorToggle::OnEnterCollider()
{
	CurrentColor.R = FMath::FRandRange(0.0f, 1.0f);
	CurrentColor.G = FMath::FRandRange(0.0f, 1.0f);
	CurrentColor.B  = FMath::FRandRange(0.0f, 1.0f);
}

// Called every frame
void AColorToggle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


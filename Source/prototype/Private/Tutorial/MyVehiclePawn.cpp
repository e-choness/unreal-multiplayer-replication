// Fill out your copyright notice in the Description page of Project Settings.


#include "Tutorial/MyVehiclePawn.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

AMyVehiclePawn::AMyVehiclePawn()
{
	// Create a camera boom on the front of the vehicle
	CameraFrontBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraFrontBoom"));
	CameraFrontBoom->SetupAttachment(RootComponent);
	CameraFrontBoom->TargetArmLength = 400.0f;
	CameraFrontBoom->bUsePawnControlRotation = true;

	// Create a camera on the front of the vehicle
	CameraFront = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraFront"));
	CameraFront->SetupAttachment(CameraFrontBoom, USpringArmComponent::SocketName);
	CameraFront->bUsePawnControlRotation = false;
}

void AMyVehiclePawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void AMyVehiclePawn::BeginPlay()
{
	Super::BeginPlay();
}

void AMyVehiclePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMyVehiclePawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

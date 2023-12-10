// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "Follower.generated.h"

// UENUM(BlueprintType)
// enum EColors
// {
// 	Red UMETA(DisplayName = "Red"),
// 	Green UMETA(DisplayName = "Green"),
// 	Blue UMETA(DisplayName = "Blue")
// };

UCLASS()
class INTROPROJECT_API AFollower : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AFollower();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Main pawn camera
	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* CameraMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

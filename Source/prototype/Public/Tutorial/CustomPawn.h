// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CustomPawn.generated.h"

class USceneComponent;

UCLASS()
class PROTOTYPE_API ACustomPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACustomPawn();

	// Reference to visible scene component
	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> VisibleComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CustomPawn|CameraSettings")
	FVector CameraPosition = FVector(-250.0f, 0.0f, 250.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CustomPawn|CameraSettings")
	FRotator CameraRotation = FRotator(-45.0f, 0.0f, 0.0f);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FVector CurrentVelocity = FVector::Zero();

	bool bGrowing = false;
	
	void Move_XAxies(float AxisValue);

	void Move_YAxies(float AxisValue);

	void StartGrowing();

	void StopGrowing();
};

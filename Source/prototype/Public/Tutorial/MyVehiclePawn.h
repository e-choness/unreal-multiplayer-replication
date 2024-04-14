// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "MyVehiclePawn.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API AMyVehiclePawn : public AWheeledVehiclePawn
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera, meta=(AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraFrontBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera, meta=(AllowPrivateAccess = "true"))
	class UCameraComponent* CameraFront;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera, meta=(AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBackBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera, meta=(AllowPrivateAccess = "true"))
	class UCameraComponent* CameraBack;

public:
	AMyVehiclePawn();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	virtual void BeginPlay() override;
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

public:
	FORCEINLINE class USpringArmComponent* GetCameraFrontBoom() const { return CameraFrontBoom; }
	FORCEINLINE class UCameraComponent* GetCameraFront() const { return CameraFront; }
	FORCEINLINE class USpringArmComponent* GetCameraBackBoom() const { return CameraBackBoom; }
	FORCEINLINE class UCameraComponent* GetCameraBack() const { return CameraBack; }
	
	virtual void Tick(float DeltaSeconds) override;
};

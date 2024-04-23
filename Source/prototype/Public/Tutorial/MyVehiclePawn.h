// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "MyVehiclePawn.generated.h"

/**
 * 
 */

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class PROTOTYPE_API AMyVehiclePawn : public AWheeledVehiclePawn
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraFrontBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> CameraFront;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBackBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> CameraBack;

public:
	AMyVehiclePawn();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	virtual void BeginPlay() override;
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

public:
	FORCEINLINE USpringArmComponent* GetCameraFrontBoom() const { return CameraFrontBoom; }
	FORCEINLINE UCameraComponent* GetCameraFront() const { return CameraFront; }
	FORCEINLINE USpringArmComponent* GetCameraBackBoom() const { return CameraBackBoom; }
	FORCEINLINE UCameraComponent* GetCameraBack() const { return CameraBack; }
	
	virtual void Tick(float DeltaSeconds) override;
};

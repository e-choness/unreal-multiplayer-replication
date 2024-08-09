// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SD_MainMenuPawn.generated.h"

class UArrowComponent;
class UCameraComponent;

UCLASS()
class PROTOTYPE_API ASD_MainMenuPawn : public APawn
{
	GENERATED_BODY()
    
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Arrow", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UArrowComponent> Arrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess="ture"))
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess="true"))
	TObjectPtr<USkeletalMeshComponent> Mesh;
	
public:
	// Sets default values for this pawn's properties
	ASD_MainMenuPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	FORCEINLINE UArrowComponent* GetArrow() const { return Arrow; }
	FORCEINLINE UCameraComponent* GetCamera() const { return Camera; }
	FORCEINLINE USkeletalMeshComponent* GetMesh() const { return Mesh; }
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SDCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UDataTable;
class UPawnNoiseEmitterComponent;
struct FSDCharacterStats;

UCLASS()
class PROTOTYPE_API ASDCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASDCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera, meta=(AllowPrivateAccess="true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera, meta=(AllowPrivateAccess="true"))
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Stealth", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UPawnNoiseEmitterComponent> NoiseEmitter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess="true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess="true"))
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess="true"))
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess="true"))
	TObjectPtr<UInputAction> SprintAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess="true"))
	TObjectPtr<UInputAction> InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character", meta=(AllowPrivateAccess="true"))
	UDataTable* CharacterDataTable;

	FSDCharacterStats* CharacterStats;

	UPROPERTY()
	AActor* InteractableActor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Move
	void Move(const struct FInputActionValue& Value);

	// Look
	void Look(const FInputActionValue& Value);
	
	// Sprint Start
	void SprintStart(const FInputActionValue& Value);
	
	UFUNCTION(Server, Reliable)
	void SprintStart_Server();

	// Sprint End
	void SprintEnd(const FInputActionValue& Value);
	
	UFUNCTION(Server, Reliable)
	void SprintEnd_Server();

	bool IsSprinting() const;

	// Interact
	void Interact(const FInputActionValue& Value);

	UFUNCTION(Server, Reliable)
	void Interact_Server();
	
	void DetectInteractable();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void UpdateCharacterStats(int32 CharacterLevel);

protected:

	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

public:
	FORCEINLINE FSDCharacterStats* GetCharacterStats() const { return CharacterStats; }
};

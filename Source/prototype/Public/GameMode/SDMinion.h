// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameMode/SDMinionStats.h"
#include "SDMinion.generated.h"

class UPawnSensingComponent;
class USphereComponent;
class UNavigationSystemV1;
struct FNavLocation;

UCLASS()
class PROTOTYPE_API ASDMinion : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Minion Perception", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UPawnSensingComponent> PawnSense;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Minion Perception", meta=(AllowPrivateAccess="true"))
	TObjectPtr<USphereComponent> Collision;

	UPROPERTY()
	UNavigationSystemV1* NavigationSystemV1;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	FSDMinionStats MinionStats;

public:
	// Sets default values for this character's properties
	ASDMinion();
	
	virtual void PostInitializeComponents() override;

	UFUNCTION(BlueprintCallable, Category="Minion AI")
	void SetNextPatrolLocation();

	UFUNCTION(Blueprintable, Category="Minion AI")
	void RestartPatrol();
	
	UFUNCTION()
	bool IsChasing() const;

	UFUNCTION()
	bool IsMoving() const;
	
	UFUNCTION(BlueprintCallable, Category="Minion AI")
	void Chase(APawn* Pawn);

	UFUNCTION()
	void OnPawnDetected(APawn* Pawn);

	UFUNCTION()
	void OnHearNoises(APawn* PawnInstigator, const FVector& Location, float Volume);

	UFUNCTION()
	void OnBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION(BlueprintCallable, Category="Minion AI")
	void GoToLocation(const FVector& Location);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle PatrolTimer;

	FNavLocation PatrolLocation;
	
	bool IsRestartPatrolling;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE UPawnSensingComponent* GetPawnSense() const { return PawnSense; }
	FORCEINLINE USphereComponent* GetSphereComponent() const { return Collision; }
};

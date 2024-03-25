// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingActor.generated.h"

UCLASS()
class PROTOTYPE_API AFloatingActor : public AActor
{
	GENERATED_BODY()


public:	
	// Sets default values for this actor's properties
	AFloatingActor();

	// Visual static mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	UStaticMeshComponent* OurVisualMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FloatingActor")
	float FloatScalar = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FloatingActor")
	float RotationSpeed = 20.0f;

	// Set domain entered state
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly)
	void SetDomainEnter(bool bToggle);

	UFUNCTION(BlueprintImplementableEvent)
	void OnDomainEnter(bool bSkipAnimation);

	UFUNCTION(BlueprintImplementableEvent)
	void OnDomainExit(bool bSkipAnimation);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// On pawns enter trigger domain
	void OnEnterDomainChanged(bool bSkipAnimation);

	// Get lifetime replicated props, since we have bIsEntered as replicated property
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_bIsEntered();

	UPROPERTY(ReplicatedUsing=OnRep_bIsEntered)
	bool bIsEntered;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

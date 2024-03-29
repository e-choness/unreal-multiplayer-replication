// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ColorToggle.generated.h"

UCLASS()
class PROTOTYPE_API AColorToggle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AColorToggle();

	// Get lifetime replicated properties
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Sphere component as root component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	class USphereComponent* SphereComponent;

	// Static Mesh as a visual presentation
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components")
	class UStaticMeshComponent *StaticMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Event called upon player enter collision
	UFUNCTION(BlueprintCallable, Category = "Toggle")
	void OnEnterCollider();
	
	UFUNCTION()
	void OnRep_CurrentColor();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Current color presentation for the cube
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing=OnRep_CurrentColor)
	FColor CurrentColor;
};

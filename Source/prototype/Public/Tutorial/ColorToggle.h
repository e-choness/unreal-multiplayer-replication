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

	// Sphere component used to detect collision
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	class USphereComponent* SphereComponent;

	// Static Mesh as a visual presentation
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components")
	class UStaticMeshComponent* StaticMeshComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Event called upon player enter collision
	UFUNCTION(Category = "Toggle")
	void OnEnterCollider();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Current color presentation for the cube
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Color")
	FColor CurrentColor;
};

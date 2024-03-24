// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingActor.generated.h"

UCLASS()
class PROTOTYPE_API AFloatingActor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere);
	UStaticMeshComponent* VisualMesh;
	
public:	
	// Sets default values for this actor's properties
	AFloatingActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FloatingActor")
	float FloatScalar = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FloatingActor")
	float RotationSpeed = 20.0f;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// F

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

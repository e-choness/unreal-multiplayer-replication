// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SDMinionSpawner.generated.h"

class ASDMinion;
class UBoxComponent;

UCLASS()
class PROTOTYPE_API ASDMinionSpawner : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Spawn System", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UBoxComponent> SpawnArea;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Spawn System", meta=(AllowPrivateAccess="true"))
	TArray<TSubclassOf<ASDMinion>> SpawnableMinions;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Spawn System", meta=(AllowPrivateAccess="true"))
	float SpawnDelay = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Spawn System", meta=(AllowPrivateAccess="true"))
	int32 MinionsAtStart = 5;

	UPROPERTY()
	FTimerHandle SpawnTimerHandle;
	
public:	
	// Sets default values for this actor's properties
	ASDMinionSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void Spawn();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GMFramework.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API AGMFramework : public AGameMode
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void SpawnPlayer(APlayerController* PlayerController);

	UFUNCTION(BlueprintPure)
	FTransform FindRandomPlayerStart() const;
	
};

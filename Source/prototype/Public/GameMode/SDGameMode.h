// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SDGameMode.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogSDGameMode, Log, All);

class AActor;

/**
 * 
 */
UCLASS()
class PROTOTYPE_API ASDGameMode : public AGameMode
{
	GENERATED_BODY()

	ASDGameMode();
public:
	UFUNCTION(BlueprintCallable, Category="Minions")
	void AlertMinions(AActor* AlertInstigator, const FVector& Location, float Radius);
	
};

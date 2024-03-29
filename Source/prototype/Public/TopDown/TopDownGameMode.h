// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TopDownGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API ATopDownGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	/** Return the best player start for this player to spawn from **/
	// UFUNCTION(BlueprintNativeEvent, Category=Game)
	AActor* ChoosePlayerStart(AController* Player);

public:
	/** Root Component **/
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Default")
	TObjectPtr<class USceneComponent> DefaultSceneRoot;

	/** Skin materials **/
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Default")
	TArray<UMaterialInterface*>  SkinMaterials;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Default")
	int SkinCount;
};
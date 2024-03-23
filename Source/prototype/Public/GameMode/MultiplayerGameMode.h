// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MultiplayerGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API AMultiplayerGameMode : public AGameMode
{
	GENERATED_BODY()

protected:

	
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void BeginPlay() override;
	virtual bool ReadyToStartMatch_Implementation() override;
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;
	
	UPROPERTY()
	TArray<APlayerController*> PlayerControllers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Multiplayer|Settings")
	int32 MinimumPlayerCount = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Multiplayer|Settings")
	float MaxWaitTime = 10.0f;
	
	UPROPERTY()
	FTimerHandle WaitingTimer;
};

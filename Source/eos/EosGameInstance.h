// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "EosGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class EOS_API UEosGameInstance : public UGameInstance
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category="EOS Functions")
	void LoginWithEos(FString Id, FString Token, FString LoginType);
	
	void LoginWithEosOnComplete(int32 LocalUserNum, bool WasSuccess, const FUniqueNetId& UserId, const FString& Error);
};

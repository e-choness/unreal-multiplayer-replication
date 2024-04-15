// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SDPlayerState.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnXpChanged, int32, NewXp);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterLevelUp, int32, NewLevelXp);

UCLASS()
class PROTOTYPE_API ASDPlayerState : public APlayerState
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, ReplicatedUsing="OnRep_Xp", Category="Experience")
	int Xp = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, ReplicatedUsing="OnRep_CharacterLevelUp", Category="Experience")
	int CharacterLevel = 1;

	UFUNCTION()
	void OnRep_Xp(int32 OldValue) const;

	UFUNCTION()
	void OnRep_CharacterLevelUp(int32 OldValue) const;

public:

	UFUNCTION(BlueprintCallable, Category="Experience")
	void AddXp(const int32 Value);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
protected:

	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnXpChanged OnXpChanged;

	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnCharacterLevelUp OnCharacterLevelUp;
};

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameMode/SDCharacter.h"
#include "SDInteractable.generated.h"

class ASDCharacter;

UINTERFACE(MinimalAPI, Blueprintable)
class USDInteractable : public UInterface{
	GENERATED_BODY()
};

class PROTOTYPE_API ISDInteractable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Interaction", meta=(DisplayName="Use"))
	void Use(ASDCharacter* CharacterInstigator);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Interaction", meta=(DisplayName="CanUse"))
	bool CanUse(ASDCharacter* CharacterInstigator) const;
};
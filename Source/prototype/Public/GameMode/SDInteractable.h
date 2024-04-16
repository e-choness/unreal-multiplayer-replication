#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
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
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Interaction", meta=(DisplayName="Interact"))
	void Interact(ASDCharacter* CharacterInstigator);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Interactin", meta=(DisplayName="Can Interact"))
	bool CanInteract(ASDCharacter* CharacterInstigator) const;
};
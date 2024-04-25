#pragma once

#include "CoreMinimal.h"
#include "SDMinionStats.generated.h"

USTRUCT(BlueprintType)
struct PROTOTYPE_API FSDMinionStats 
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float PatrolSpeed = 150.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ChaseSpeed = 350.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float PatrolRadius = 50000.0f;
};
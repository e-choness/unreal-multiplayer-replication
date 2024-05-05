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
	float PatrolRadius = 1500.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float PatrolThreshold = 500.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float PatrolRestartTime = 3.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AlertRadius = 6000.0f;
};
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SDCharacterStats.generated.h"

USTRUCT(BlueprintType)
struct PROTOTYPE_API FSDCharacterStats : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float WalkSpeed = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float SprintSpeed = 400.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Damage")
	float DamageMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Damange")
	float StealthMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="XP")
	int32 NextLevelXp = 10;
	
};

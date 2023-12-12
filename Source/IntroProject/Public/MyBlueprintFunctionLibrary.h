// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBlueprintFunctionLibrary.generated.h"

USTRUCT(BlueprintType)
struct FAverages
{
	FAverages() :
		Mean(0.0f),
		Modal(0.0f),
		Median(0.0f) {};

	FAverages(double InMean, double InMode, double InMedian ) :
		Mean(InMean),
		Modal(InMode),
		Median(InMedian) {};
	
	UPROPERTY(BlueprintReadOnly)
	float Mean = 0.0f;
	
	UPROPERTY(BlueprintReadOnly)
	float Modal = 0.0f;

	UPROPERTY(BlueprintReadOnly)
	float Median = 0.0f;
	
	GENERATED_BODY()
};
/**
 * 
 */
UCLASS()
class INTROPROJECT_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
public:
	// Returns a message
	UFUNCTION(BlueprintCallable)
	static FString GetBlueprintLibraryMessage();

	// Get golden ratio value
	UFUNCTION(BlueprintCallable, BlueprintPure,
		meta = (ToolTip = "The perfect ratio, golden rule of the world.",
			CompactNodeTitle = "Φ"))
		static double GetMyPhi();

	// Calculate an array's mean, mode and median
	UFUNCTION(BlueprintCallable,
		meta = (ToolTip = "Calculate the mean, mode and median of an array."))
		// const means the function cannot modify the array's value
		static FAverages CalculateAverages(const TArray<double> InValues);

protected:

private:
	static constexpr double phi = 1.618033988749894f;
	GENERATED_BODY()
	
};



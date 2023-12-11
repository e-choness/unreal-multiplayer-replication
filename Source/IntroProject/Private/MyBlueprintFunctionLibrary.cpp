// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBlueprintFunctionLibrary.h"

FString UMyBlueprintFunctionLibrary::GetBlueprintLibraryMessage(){
	return FString(TEXT("This is a message, but it's from a blueprint library."));
}

double UMyBlueprintFunctionLibrary::GetMyPhi()
{
	return phi;
}

FAverages UMyBlueprintFunctionLibrary::CalculateAverages(const TArray<double> InValues)
{
	// Calculate mean;
	int32 Sum = 0;
	for(auto& Num: InValues)
	{
		Sum += Num;
	}
	double Mean = Sum/InValues.Num();

	// Calculate mode
	double Mode = 0.0f;
	auto Map = TMap<double, int32>();
	for(const auto& Num : InValues)
	{
		if(!Map.FindKey(Num))
		{
			Map.Add(Num, 1);
		}
		else
		{
			Map[Num] += 1;
		}
	}

	int Max = 0;
	for(const auto& Pair: Map)
	{
		if(Pair.Value > Max)
		{
			Max = Pair.Value;
			Mode = Pair.Key;
		}
	}

	
	
	return FAverages
}

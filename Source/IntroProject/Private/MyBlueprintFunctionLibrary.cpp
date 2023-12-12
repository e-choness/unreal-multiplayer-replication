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
	// Declare 
	TMap<double, int32> Map;
	auto TempArray = InValues;
	
	double Mean = 0.0f;
	double Mode = 0.0f;
	double Median = 0.0f;
	
	double Sum = 0;
	const int32 Count = TempArray.Num();

	if(Count == 0) return FAverages(Mean, Mode, Median);

	TempArray.Sort();
	for(const auto& Num: TempArray)
	{
		// Sum is for calculating Mean
		Sum += Num;

		// 
		if(Map.Contains(Num))
		{
			Map[Num] ++;
		}else
		{
			Map.Add(Num, 1);
		}
	}

	Mean = Sum/static_cast<double>(Count);

	// Sort 
	Map.ValueSort([](int32 A, int32 B){return A>B; });

	// TArray<TPair<int32, int32> Modals = Map.Array();
	
	return FAverages(Mean,Mode, Median);
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerFramework/GMFramework.h"

#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"


void AGMFramework::SpawnPlayer(APlayerController* PlayerController)
{
	const auto ControlledPawn = PlayerController->GetPawn();
	if(IsValid(ControlledPawn))
	{
		ControlledPawn->Destroy(true);
	}else
	{
		const auto RandomPlayerStart = FindRandomPlayerStart();
	}
}

FTransform AGMFramework::FindRandomPlayerStart() const
{
	// Create an array to store all player start in the level
	TArray<AActor*> AllPlayerStart;
	
	// Get all actor instance of PlayerStart class
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), AllPlayerStart);

	// Default information of Player Start transform
	FTransform PlayerStartTransform = FTransform();

	// If any Player Starts is found return random 
	if(AllPlayerStart.Num()>=1)
	{
		const int Index = FMath::RandRange(0, AllPlayerStart.Num()-1);
		const auto RandomPlayerStart = AllPlayerStart[Index];
		PlayerStartTransform = RandomPlayerStart->GetTransform();
	}

	return PlayerStartTransform;
}

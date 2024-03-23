// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/MultiplayerGameMode.h"

void AMultiplayerGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	PlayerControllers.AddUnique(NewPlayer);

	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Post login happens!"));	
	if(PlayerControllers.Num() >= MinimumPlayerCount)
	{
		if(!HasMatchStarted())
		{
			StartMatch();
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Match starts!"));
			GetWorld()->GetTimerManager().ClearTimer(WaitingTimer);
		}
	}
}

void AMultiplayerGameMode::BeginPlay()
{
	Super::BeginPlay();
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Play begins!"));	
	GetWorld()->GetTimerManager().SetTimer(
				WaitingTimer,
				this,
				&AMultiplayerGameMode::StartMatch,
				MaxWaitTime,
				false);
}

bool AMultiplayerGameMode::ReadyToStartMatch_Implementation()
{
	Super::ReadyToStartMatch_Implementation();
	if(GEngine && PlayerControllers.Num() >= MinimumPlayerCount)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Ready to start match!"));	
	return PlayerControllers.Num() >= MinimumPlayerCount;
}

void AMultiplayerGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	RestartPlayer(NewPlayer);
}

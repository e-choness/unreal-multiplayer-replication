// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/SDGameMode.h"

#include "GameMode/SDGameState.h"
#include "GameMode/SDPlayerController.h"
#include "GameMode/SDPlayerState.h"

ASDGameMode::ASDGameMode()
{
	GameStateClass = ASDGameState::StaticClass();
	PlayerControllerClass = ASDPlayerController::StaticClass();
	PlayerStateClass = ASDPlayerState::StaticClass();

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ShadowDungeon/Pawns/BP_Character"));

	if(PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

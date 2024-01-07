// Copyright Epic Games, Inc. All Rights Reserved.

#include "eosGameMode.h"
#include "eosCharacter.h"
#include "UObject/ConstructorHelpers.h"

AeosGameMode::AeosGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

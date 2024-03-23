// Copyright Epic Games, Inc. All Rights Reserved.

#include "prototypeGameMode.h"
#include "prototypeCharacter.h"
#include "UObject/ConstructorHelpers.h"

AprototypeGameMode::AprototypeGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

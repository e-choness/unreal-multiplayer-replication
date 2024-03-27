// Copyright Epic Games, Inc. All Rights Reserved.

#include "PrototypeGameMode.h"
#include "PrototypeCharacter.h"
#include "UObject/ConstructorHelpers.h"

APrototypeGameMode::APrototypeGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

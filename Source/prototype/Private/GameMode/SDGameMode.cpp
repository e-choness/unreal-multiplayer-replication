// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/SDGameMode.h"

#include "GameMode/SDCustomLogs.h"
#include "GameMode/SDGameState.h"
#include "GameMode/SDPlayerController.h"
#include "GameMode/SDPlayerState.h"
#include "GameMode/SDMinion.h"
#include "Kismet/GameplayStatics.h"
#include "Logging/StructuredLog.h"

DEFINE_LOG_CATEGORY(LogSDGameMode)

ASDGameMode::ASDGameMode()
{
	GameStateClass = ASDGameState::StaticClass();
	PlayerControllerClass = ASDPlayerController::StaticClass();
	PlayerStateClass = ASDPlayerState::StaticClass();

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ShadowDungeon/Actors/BP_Character"));

	if(PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ASDGameMode::AlertMinions(AActor* AlertInstigator, const FVector& Location, float Radius)
{
	// Both LOG and LOGFMT are showing up, they are working
	UE_LOG(LogSDGameMode, Log, TEXT("Regular, alert minions")); 
	UE_LOGFMT(LogSDGameMode, Log, "Alert Minions.");
	
	UE_LOGFMT(LogPrototype, Log, "Custom, Alert Minions."); // This one never shows up in the output log section
	
	TArray<AActor*> Minions;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASDMinion::StaticClass(), Minions);

	for(const auto Minion: Minions)
	{
		if(AlertInstigator == Minion) continue;
		if(const auto Distance = FVector::Distance(AlertInstigator->GetActorLocation(), Minion->GetActorLocation()); Distance<Radius)
		{
			if(const auto MinionCharacter = Cast<ASDMinion>(Minion))
			{
				MinionCharacter->GoToLocation(Location);
			}
		}
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/SDPlayerState.h"

#include "GameMode/SDCharacter.h"
#include "GameMode/SDCharacterStats.h"
#include "Net/UnrealNetwork.h"


void ASDPlayerState::OnRep_Xp(int32 OldValue) const
{
	OnXpChanged.Broadcast(Xp);
}

void ASDPlayerState::OnRep_CharacterLevelUp(int32 OldValue) const
{
	OnCharacterLevelUp.Broadcast(CharacterLevel);
}

void ASDPlayerState::AddXp(const int32 Value)
{
	Xp += Value;
	OnXpChanged.Broadcast(Xp);

	GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Yellow, FString::Printf(TEXT("Total Xp: %d"), Xp));

	if(const auto Character = Cast<ASDCharacter>(GetPawn()))
	{
		if(Character->GetCharacterStats()->NextLevelXp < Xp)
		{
			GEngine->AddOnScreenDebugMessage(3, 5.0f, FColor::Green, TEXT("Level Up!"));

			CharacterLevel++;
			Character->UpdateCharacterStats(CharacterLevel);
			OnCharacterLevelUp.Broadcast(CharacterLevel);
		}
	}
}

void ASDPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ASDPlayerState, Xp, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(ASDPlayerState, CharacterLevel, COND_OwnerOnly);
}

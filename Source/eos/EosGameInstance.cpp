// Fill out your copyright notice in the Description page of Project Settings.


#include "EosGameInstance.h"
#include "Logging/StructuredLog.h"
#include "OnlineSubsystemUtils.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineIdentityInterface.h"

void UEosGameInstance::LoginWithEos(FString Id, FString Token, FString LoginType)
{
	IOnlineSubsystem *SubSystemRef = Online::GetSubsystem(this->GetWorld());
	if(SubSystemRef)
	{
		IOnlineIdentityPtr IdentityPtr = SubSystemRef->GetIdentityInterface();
		if(IdentityPtr)
		{
			FOnlineAccountCredentials AccountCredentials;
			AccountCredentials.Id = Id;
			AccountCredentials.Token = Token;
			AccountCredentials.Type = LoginType;

			IdentityPtr->OnLoginCompleteDelegates->AddUObject(this, &UEosGameInstance::LoginWithEosOnComplete);
			IdentityPtr->Login(0, AccountCredentials);
		}
	}
	
}

void UEosGameInstance::LoginWithEosOnComplete(int32 LocalUserNum, bool WasSuccess, const FUniqueNetId& UserId,
	const FString& Error)
{
	if(WasSuccess)
	{
		UE_LOGFMT(LogTemp, Log, "The client successfully logged in.");
	}

	UE_LOGFMT(LogTemp, Error, "The client failed to login. Error: {0}", *Error);
}

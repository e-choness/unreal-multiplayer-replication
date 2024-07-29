// Fill out your copyright notice in the Description page of Project Settings.

#include "LiveOps/LoginActor.h"
#include "Core/PlayFabClientAPI.h"

// Sets default values
ALoginActor::ALoginActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALoginActor::BeginPlay()
{
	Super::BeginPlay();

	GetMutableDefault<UPlayFabRuntimeSettings>()->TitleId = TEXT("144");

	ClientAPI = IPlayFabModuleInterface::Get().GetClientAPI();

	PlayFab::ClientModels::FLoginWithCustomIDRequest request;
	request.CustomId = TEXT("GettingStartedLogin");
	request.CreateAccount = true;

	ClientAPI->LoginWithCustomID(request,
		PlayFab::UPlayFabClientAPI::FLoginWithCustomIDDelegate::CreateUObject(this, &ALoginActor::OnSuccess),
		PlayFab::FPlayFabErrorDelegate::CreateUObject(this, &ALoginActor::OnError));
}

void ALoginActor::OnSuccess(const PlayFab::ClientModels::FLoginResult& Result) const
{
	UE_LOG(LogTemp, Log, TEXT("This is my first successful PlayFab API call!"));
}

void ALoginActor::OnError(const PlayFab::FPlayFabCppError& ErrorResult) const
{
	UE_LOG(LogTemp, Error, TEXT("Something went wrong with the first API call.\nError message: %s"), *ErrorResult.GenerateErrorReport());
}

// Called every frame
void ALoginActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


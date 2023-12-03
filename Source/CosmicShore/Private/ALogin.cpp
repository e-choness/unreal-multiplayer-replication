// Fill out your copyright notice in the Description page of Project Settings.


#include "ALogin.h"
#include "Core/PlayFabClientAPI.h"

// Sets default values
AALogin::AALogin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AALogin::BeginPlay()
{
	Super::BeginPlay();

	PlayFab::ClientModels::FLoginWithCustomIDRequest Request;
	Request.CustomId = TEXT("GettingPlayFabStarted");
	Request.CreateAccount = true;

	UE_LOG(LogTemp, Log, TEXT("Login Actor is getting started."));

	ClientAPI->LoginWithCustomID(Request,
		PlayFab::UPlayFabClientAPI::FLoginWithCustomIDDelegate::CreateUObject(this, &AALogin::OnSuccess),
		PlayFab::FPlayFabErrorDelegate::CreateUObject(this, &AALogin::OnError));
}

void AALogin::OnSuccess(const PlayFab::ClientModels::FLoginResult& Result) const
{
	UE_LOG(LogTemp, Log, TEXT("This is my first PlayFab Login."));
}

void AALogin::OnError(const PlayFab::FPlayFabCppError& Error) const
{
	UE_LOG(LogTemp, Log, TEXT("Unknown nightmare with my first PlayFab Login."));
}

// Called every frame
void AALogin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


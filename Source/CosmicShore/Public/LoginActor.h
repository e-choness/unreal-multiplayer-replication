// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayFab.h"
#include "Core/PlayFabError.h"
#include "Core/PlayFabClientDataModels.h"
#include "LoginActor.generated.h"


UCLASS()
class COSMICSHORE_API ALoginActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALoginActor();

	// PlayFab authentication success event
	void OnSuccess(const PlayFab::ClientModels::FLoginResult& Result) const;

	// PlayFab authentication error event
	void OnError(const PlayFab::FPlayFabCppError& ErrorResult) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
private:
	PlayFabClientPtr ClientAPI = nullptr;
};

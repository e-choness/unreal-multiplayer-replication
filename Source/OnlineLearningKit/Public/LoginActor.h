#pragma once

#include "CoreMinimal.h"
#include "GameFramework//Actor.h"
#include "PlayFab.h"
#include "Core/PlayFabError.h"
#include "Core/PlayFabClientDataModels.h"
#include "LoginActor.generated.h"

UCLASS()
class ALoginActor : public AActor
{
	GENERATED_BODY()
public:
	ALoginActor();
	virtual void BeginPlay() override;
	void OnSuccess(const PlayFab::ClientModels::FLoginResult& Result) const;
	void OnError(const PlayFab::FPlayFabCppError& ErrorResult) const;

	virtual void Tick(float DeltaSeconds) override;
private:
	PlayFabClientPtr clientAPI = nullptr;
};
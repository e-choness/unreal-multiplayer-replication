#include "LoginActor.h"
#include "Core/PlayFabClientAPI.h"

ALoginActor::ALoginActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ALoginActor::BeginPlay()
{
	Super::BeginPlay();

	clientAPI = IPlayFabModuleInterface::Get().GetClientAPI();

	PlayFab::ClientModels::FLoginWithCustomIDRequest request;
	request.CustomId = TEXT("OnlineLearningKit");
	request.CreateAccount = true;

	clientAPI->LoginWithCustomID(request,
		PlayFab::UPlayFabClientAPI::FLoginWithCustomIDDelegate::CreateUObject(this, &ALoginActor::OnSuccess),
		PlayFab::FPlayFabErrorDelegate::CreateUObject(this, &ALoginActor::OnError)
		);
}

void ALoginActor::OnSuccess(const PlayFab::ClientModels::FLoginResult& Result) const
{
	UE_LOG(LogTemp, Log, TEXT("Congratulations, this is my first login!"));
}

void ALoginActor::OnError(const PlayFab::FPlayFabCppError& ErrorResult) const
{
	UE_LOG(LogTemp, Error, TEXT("Unknown nightmare with this one."));
}

void ALoginActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

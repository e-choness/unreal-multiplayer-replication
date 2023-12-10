// Fill out your copyright notice in the Description page of Project Settings.

#include "IntroProject/Public/Follower.h"
#include "Logging/StructuredLog.h"

// Sets default values
AFollower::AFollower()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create components
    CameraMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CameraMesh"));
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

    //  Setup camera
	Camera->FieldOfView = 120.f;
	Camera->SetupAttachment(CameraMesh);
	Camera->SetRelativeLocation(FVector(100.0f, 0.0f, 50.0f));

    const auto Vector = FVector(0.0f, 0.0f, 0.0f);
	UE_LOGFMT(LogTemp, Log, "The vector value is: {0}", Vector.ToString());

	auto Array = TArray<int>();
	Array.Init(10, 5);
	for(auto& Num : Array)
	{
		UE_LOGFMT(LogTemp, Log, "The array element is: {0}", Num);
	}

	FString Arr[] = {TEXT("of"), TEXT("Tomorrow")};

	for(auto& Txt: Arr)
	{
		UE_LOGFMT(LogTemp, Log, "The array element is: {0}", Txt);
	}

	// auto Color = EColors();
	// UE_LOGFMT(LogTemp, Log, "The enum colors are: {0} {1} {2}", Color);
	
}

// Called when the game starts or when spawned
void AFollower::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFollower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFollower::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


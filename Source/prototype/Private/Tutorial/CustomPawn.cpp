// Fill out your copyright notice in the Description page of Project Settings.


#include "tutorial/CustomPawn.h"
#include "Camera/CameraComponent.h"

// Sets default values
ACustomPawn::ACustomPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set this pawn to be controlled by the lowest-numbered player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Initialize Visible Scene Component
	// Create a dummy root component we can attach things to
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// Create a camera and a visible object
	UCameraComponent* CustomCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	VisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisibleComponent"));

	// Attach camera to the root component.
	CustomCamera->SetupAttachment(RootComponent);

	// Set camera offset and rotation 
	CustomCamera->SetRelativeLocationAndRotation(CameraPosition, CameraRotation);

	// Attach visible object to the root component.
	VisibleComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACustomPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACustomPawn::Move_XAxies(float AxisValue)
{
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void ACustomPawn::Move_YAxies(float AxisValue)
{
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void ACustomPawn::StartGrowing()
{
	bGrowing = true;
}

void ACustomPawn::StopGrowing()
{
	bGrowing = false;
}


// Called every frame
void ACustomPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Handle growing and shrinking based on "Grow" action
	float CurrentScale = VisibleComponent->GetComponentScale().X;
	if(bGrowing)
	{
		// Grow to double size over the course of one second
		CurrentScale += DeltaTime;
	}else
	{
		// Shrink to half as fast as we grow
		CurrentScale -= DeltaTime * 0.5f;
	}

	// Make sure we never drop below starting size, or grow past double size
	CurrentScale = FMath::Clamp(CurrentScale, 1.0f, 2.0f);
	VisibleComponent->SetWorldScale3D(FVector(CurrentScale));

	// Handle movement
	if(!CurrentVelocity.IsZero())
	{
		FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
		SetActorLocation(NewLocation);
	}
	
}

// Called to bind functionality to input
void ACustomPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind grow actions with when Space is pressed and released 
	InputComponent->BindAction("Grow", IE_Pressed, this, &ACustomPawn::StartGrowing);
	InputComponent->BindAction("Grow", IE_Released, this, &ACustomPawn::StopGrowing);

	// Bind movement actions
	InputComponent->BindAxis("MoveX", this, &ACustomPawn::Move_XAxies);
	InputComponent->BindAxis("MoveY", this, &ACustomPawn::Move_YAxies);
}


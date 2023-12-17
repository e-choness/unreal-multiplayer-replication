// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerBB.h"
#include "CharacterBB.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void APlayerControllerBB::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// Store a reference to the Player's Pawn
	PlayerCharacter = Cast<ACharacterBB>(InPawn);
	checkf(PlayerCharacter, TEXT("APlayerControllerBB derived classes should only posses ACharacterBBBase classes."));

	// Get a reference to the EnhancedInputComponent
	EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	checkf(EnhancedInputComponent, TEXT("Unable to get reference to the EnhancedInputComponent."));

	// Bind the input actions.
	// Only attempt to bind if a valid value was provided
	if(ActionMove)
		EnhancedInputComponent->BindAction(ActionMove, ETriggerEvent::Triggered, this, &APlayerControllerBB::HandleMove);

	if(ActionLook)
		EnhancedInputComponent->BindAction(ActionLook, ETriggerEvent::Triggered, this, &APlayerControllerBB::HandleLook);

	if(ActionJump)
		EnhancedInputComponent->BindAction(ActionLook, ETriggerEvent::Triggered, this, &APlayerControllerBB::HandleJump);
}

void APlayerControllerBB::OnUnPossess()
{
	Super::OnUnPossess();
}

void APlayerControllerBB::HandleMove(const FInputActionValue& InputActionValue)
{
	// Value is a Vector2D
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	// Add movement to the Player's Character Pawn
	if(PlayerCharacter)
	{
		PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorForwardVector(), MovementVector.Y);
		PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorRightVector(), MovementVector.X);
	}
}

void APlayerControllerBB::HandleLook(const FInputActionValue& InputActionValue)
{
	// The value is a Vector2D
	const FVector2D LookVector = InputActionValue.Get<FVector2D>();

	// Add yaw and pitch input to controller
	AddYawInput(LookVector.X);
	AddPitchInput(LookVector.Y);
}

void APlayerControllerBB::HandleJump()
{
	// Input is "Digital" no value returned here

	// Make the Player's Character Pawn jump, disabling crouch if it was active
	if(PlayerCharacter)
	{
		PlayerCharacter->UnCrouch();
		PlayerCharacter->Jump();
	}
}


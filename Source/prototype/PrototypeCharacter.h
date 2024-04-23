// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PrototypeCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class APrototypeCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	/** Interact Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InteractAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> FireAction;

public:
	APrototypeCharacter();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** The player's maximum health. This is the highest value of their health. **/
	UPROPERTY(EditDefaultsOnly, Category="Health")
	float MaxHealth;

	/** The player's current health. Death when it reaches 0 **/
	UPROPERTY(ReplicatedUsing=OnRep_CurrentHealth)
	float CurrentHealth;

	/** RepNotify for changes made to current health **/
	UFUNCTION()
	void OnRep_CurrentHealth() const;

	/** Response to health being updated. Called on the server immediately **/
	UFUNCTION()
	void OnHealthUpdate() const;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay() override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	/** Getter for Max Health **/
	UFUNCTION(BlueprintPure, Category="Health")
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }

	/** Getter for Current Health **/
	UFUNCTION(BlueprintPure, Category="Health")
	FORCEINLINE float GetCurrentHealth() const { return CurrentHealth; }

	/** Setter for Current Health. Clamps the value between 0 and MaxHealth **/
	UFUNCTION(BlueprintCallable, Category="Health")
	void SetCurrentHealth(float HealthValue);

	/** Event for taking damage. Overridden from APawn **/
	UFUNCTION(BlueprintCallable, Category="Health")
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:

	UPROPERTY(EditDefaultsOnly, Category="Gameplay")
	TSubclassOf<class AThirdPersonProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category="Gameplay")
	float FireRate;

	/** If true, you are in the process of firing projectiles. **/
	bool bIsFiringWeapon;

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	/** Called for starting fire input **/
	void StartFire();

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	/** Called for ending fire input**/
	void StopFire();

	/** Server function for spawning projectiles**/
	UFUNCTION(Server, Reliable)
	void HandleFire_Server();
	
	/** A timer handle used for providing the fire rate delay in-between spawns.**/
	FTimerHandle FiringTimer;

protected:

	UFUNCTION(BlueprintCallable, Category="Gameplay")
	void Interact();

	UFUNCTION(BlueprintImplementableEvent, Category="Gamplay")
	void OnInteract();
};

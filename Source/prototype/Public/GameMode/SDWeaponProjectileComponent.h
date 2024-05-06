// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SDWeaponProjectileComponent.generated.h"


class UInputAction;
class UInputMappingContext;
class ASDWeaponProjectileBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROTOTYPE_API USDWeaponProjectileComponent : public USceneComponent
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Projectile", meta=(AllowPrivateAccess="true"))
	TSubclassOf<ASDWeaponProjectileBase> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess="true"))
	UInputMappingContext* WeaponMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess="true"))
	UInputAction* ThrowAction;

public:	
	// Sets default values for this component's properties
	USDWeaponProjectileComponent();

	UFUNCTION(BlueprintCallable, Category="Projectile")
	void SetProjectileClass(TSubclassOf<ASDWeaponProjectileBase> NewProjectileClass);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void Throw();

	UFUNCTION(Server, Reliable)
	void Throw_Server();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

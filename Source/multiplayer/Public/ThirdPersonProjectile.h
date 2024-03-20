// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ThirdPersonProjectile.generated.h"

UCLASS()
class MULTIPLAYER_API AThirdPersonProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AThirdPersonProjectile();

	// Sphere component used to test collision.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	class USphereComponent* SphereComponent;

	// Static Mesh used to provide a visual representation of the object.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	class UStaticMeshComponent* StaticMesh;

	// Movement component for handling projectile movement.
	UPROPERTY(EditAnywhere, Category="Effects")
	class UProjectileMovementComponent* ProjectileMovementComponent;

	// Particle used when the projectile impacts against another object and explodes.
	UPROPERTY(EditAnywhere, Category="Effects")
	class UParticleSystem* ExplosionEffect;

	// The damage type and damage that will be done by this projectile
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Damage")
	TSubclassOf<class UDamageType> DamageType;

	// The damage dealt by this projectile.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Damage")
	float Damage;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ThirdPersonProjectile.generated.h"

UCLASS()
class PROTOTYPE_API AThirdPersonProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AThirdPersonProjectile();

	// Sphere component used to test collision
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	class USphereComponent* SphereComponent;

	// Static Mesh used to provide a visual representation of the object
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	class UStaticMeshComponent* StaticMesh;

	// Movement Component for handling projectile movement.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	class UProjectileMovementComponent* ProjectileMovementComponent;

	// Particle used when the projectile impacts against another object and explodes.
	UPROPERTY(EditAnywhere, Category="Effects")
	class UParticleSystem* ExplosionEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Damage")
	TSubclassOf<class UDamageType> DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Damage")
	float Damage;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Destroyed when the projectile
	virtual void Destroyed() override;

	// Event called upon projectile impact
	UFUNCTION(Category = "Projectile")
	void OnProjectileImpact(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

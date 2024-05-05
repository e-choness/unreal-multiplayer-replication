// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SDWeaponProjectileBase.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
class UStaticMeshComponent;
class UPrimitiveComponent;

UCLASS()
class PROTOTYPE_API ASDWeaponProjectileBase : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	TObjectPtr<USphereComponent> Collision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon", meta=(AllowPrivateAccess="true"))
	float Damage = 1.0f;
	
public:	
	// Sets default values for this actor's properties
	ASDWeaponProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE USphereComponent* GetCollision() const { return Collision;}
	
	FORCEINLINE UStaticMeshComponent* GetStaticMesh() const { return StaticMesh;}
	
	FORCEINLINE UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
};

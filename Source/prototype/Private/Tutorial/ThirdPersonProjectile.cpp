// Fill out your copyright notice in the Description page of Project Settings.


#include "Tutorial/ThirdPersonProjectile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AThirdPersonProjectile::AThirdPersonProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set object replicate state to true
	bReplicates = true;

	// Definition for the SphereComponent that will serve as the Root component
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	SphereComponent->InitSphereRadius(37.5f);
	SphereComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	RootComponent = SphereComponent;

	// Registering the projectile impact function on a hit event
	if(GetLocalRole() == ROLE_Authority)
	{
		SphereComponent->OnComponentHit.AddDynamic(this, &AThirdPersonProjectile::OnProjectileImpact);
	}

	// Definition for the Mesh that will serve as its visual presentation
	static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultMesh(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);

	// Set the static mesh and it's position/scale if mesh is found in the file path
	if(DefaultMesh.Succeeded())
	{
		StaticMesh->SetStaticMesh(DefaultMesh.Object);
		StaticMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -37.5f));
		StaticMesh->SetRelativeScale3D(FVector(0.75f, 0.75f, 0.75f));
	}

	// Definition for explosion effect
	static ConstructorHelpers::FObjectFinder<UParticleSystem> DefaultExplosionEffect(TEXT("/Game/StarterContent/Particles/P_Explosion.P_Explosion"));
	if(DefaultExplosionEffect.Succeeded())
	{
		ExplosionEffect = DefaultExplosionEffect.Object;
	}

	// Definition for the projectile movement component
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovementComponent->SetUpdatedComponent(SphereComponent);
	ProjectileMovementComponent->InitialSpeed = 1500.0f;
	ProjectileMovementComponent->MaxSpeed = 1500.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;

	DamageType = UDamageType::StaticClass();
	Damage = 10.0f;
}

// Called when the game starts or when spawned
void AThirdPersonProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AThirdPersonProjectile::Destroyed()
{
	Super::Destroyed();
	const FVector SpawnLocation = GetActorLocation();
	UGameplayStatics::SpawnEmitterAtLocation(this, ExplosionEffect, SpawnLocation, FRotator::ZeroRotator, true, EPSCPoolMethod::AutoRelease);
}

void AThirdPersonProjectile::OnProjectileImpact(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if(OtherActor)
	{
		UGameplayStatics::ApplyPointDamage(OtherActor, Damage,NormalImpulse, Hit, GetInstigator()->Controller, this, DamageType);
	}
	Destroy();
}

// Called every frame
void AThirdPersonProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


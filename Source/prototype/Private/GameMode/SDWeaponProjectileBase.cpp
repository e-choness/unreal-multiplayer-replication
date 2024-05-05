// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/SDWeaponProjectileBase.h"

#include "GameMode/SDCharacter.h"
#include "GameMode/SDCharacterStats.h"
#include "Components/SphereComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ASDWeaponProjectileBase::ASDWeaponProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetGenerateOverlapEvents(true);
	Collision->SetSphereRadius(10.0f);
	Collision->BodyInstance.SetCollisionProfileName("BlockAll");
	Collision->OnComponentHit.AddDynamic(this, &ASDWeaponProjectileBase::OnHit);

	RootComponent = Collision;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMesh->SetupAttachment(RootComponent);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	StaticMesh->SetRelativeLocation(FVector(-40.0f, 0.0f, 0.0f));
	StaticMesh->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("/Game/KayKit/DungeonElements/dagger_common"));
	if(Mesh.Succeeded())
	{
		GetStaticMesh()->SetStaticMesh(Mesh.Object);
	}

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projetile Movement"));
	ProjectileMovement->UpdatedComponent = Collision;
	ProjectileMovement->ProjectileGravityScale = 0.0f;
	ProjectileMovement->InitialSpeed = 3000.0f;
	ProjectileMovement->MaxSpeed = 3000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;

	bReplicates = true;
}

// Called when the game starts or when spawned
void ASDWeaponProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASDWeaponProjectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	float DamageResult = Damage;
	if(const auto Character = Cast<ASDCharacter>(GetInstigator()))
	{
		DamageResult *= Character->GetCharacterStats()->DamageMultiplier;
	}

	if(OtherActor && OtherActor != this)
	{
		const FDamageEvent Event(UDamageType::StaticClass());
		OtherActor->TakeDamage(DamageResult, Event, GetInstigatorController(), this);
	}

	Destroy();
}

// Called every frame
void ASDWeaponProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


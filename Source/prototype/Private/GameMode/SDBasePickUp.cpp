// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/SDBasePickUp.h"

#include "Components/SphereComponent.h"
#include "GameMode/SDCharacter.h"

// Sets default values
ASDBasePickUp::ASDBasePickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create sphere collision and define its radius
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	RootComponent = SphereCollision;
	SphereCollision->SetGenerateOverlapEvents(true);
	SphereCollision->SetSphereRadius(200.0f);

	// Create static mesh for the actor
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(SphereCollision);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	// Set replicates to true
	bReplicates = true;
}

void ASDBasePickUp::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(const auto Character = Cast<ASDCharacter>(OtherActor))
	{
		Pickup(Character);
	}
}

void ASDBasePickUp::Pickup_Implementation(ASDCharacter* OwningCharacter)
{
	SetOwner(OwningCharacter);
}

// Called when the game starts or when spawned
void ASDBasePickUp::BeginPlay()
{
	Super::BeginPlay();

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ASDBasePickUp::OnBeginOverlap);
}

// Called every frame
void ASDBasePickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


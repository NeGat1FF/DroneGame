// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePickupItem.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABasePickupItem::ABasePickupItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

	MeshComponent->SetCollisionProfileName(TEXT("NoCollision"));

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetupAttachment(MeshComponent);
	CollisionComponent->SetSphereRadius(50.0f);
	CollisionComponent->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));


    RotationSpeed = 30.0f; // Degrees per second
    LevitationAmplitude = 20.0f; // Units
    LevitationSpeed = 2.0f; // Cycles per second
}

// Called when the game starts or when spawned
void ABasePickupItem::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABasePickupItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Rotate the item
    FRotator Rotation = GetActorRotation();
    Rotation.Yaw += RotationSpeed * DeltaTime;
    SetActorRotation(Rotation);

    // Levitate the item
    FVector Location = GetActorLocation();
    Location.Z += FMath::Sin(RunningTime * LevitationSpeed * 2.0f * PI) * LevitationAmplitude * DeltaTime;
    SetActorLocation(Location);

    RunningTime += DeltaTime;
}

void ABasePickupItem::OnPickup(AActor *ActorThatPickedUp)
{
	Destroy();
}

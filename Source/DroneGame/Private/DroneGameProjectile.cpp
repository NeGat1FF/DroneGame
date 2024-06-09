// Fill out your copyright notice in the Description page of Project Settings.


#include "DroneGameProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DamageableInterface.h"

// Sets default values
ADroneGameProjectile::ADroneGameProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = CollisionComponent;
	CollisionComponent->InitSphereRadius(7.0f);
	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("BlockAll"));
	CollisionComponent->SetNotifyRigidBodyCollision(true);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->UpdatedComponent = CollisionComponent;
	ProjectileMovement->InitialSpeed = 3000.0f;
	ProjectileMovement->MaxSpeed = 3000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	InitialLifeSpan = 10.0f;

}

// Called when the game starts or when spawned
void ADroneGameProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionComponent->OnComponentHit.AddDynamic(this, &ADroneGameProjectile::OnHit);
}

// Called every frame
void ADroneGameProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADroneGameProjectile::OnHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent, FVector NormalImpulse, const FHitResult &Hit)
{
	if (OtherActor)
	{
		if (IDamageableInterface *Damageable = Cast<IDamageableInterface>(OtherActor))
		{
			// Do random damage between 10 and 20
			Damageable->Damage(FMath::RandRange(10, 20));
		}
	}
	Destroy();
}

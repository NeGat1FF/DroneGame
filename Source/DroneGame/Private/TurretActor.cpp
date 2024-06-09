// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "DroneGameProjectile.h"
#include "DronePawn.h"

// Sets default values
ATurretActor::ATurretActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	RootComponent = TurretMesh;
	TurretMesh->SetCollisionProfileName(TEXT("BlockAll"));

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetupAttachment(TurretMesh);
	CollisionComponent->SetCollisionProfileName(TEXT("OverlapAll"));
}

// Called when the game starts or when spawned
void ATurretActor::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ATurretActor::OnComponentBeginOverlap);
	CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ATurretActor::OnComponentEndOverlap);
}

void ATurretActor::Fire()
{
	if(bCanFire && Target && Target->GetHealth() > 0){
		// Chech if the target is in line of sight
		FHitResult HitResult;
		FVector StartLocation = TurretMesh->GetComponentLocation();
		FVector EndLocation = Target->GetActorLocation();

		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this);

		if(GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_GameTraceChannel1, CollisionParams)){
			if(Cast<ADronePawn>(HitResult.GetActor()) == Target){
				// Fire the projectile
				FVector SpawnLocation = GetActorLocation() + (Target->GetActorLocation() - GetActorLocation()).GetSafeNormal() * 100.0f;
				// Calculate the rotation of the projectile
				FRotator SpawnRotation = FRotationMatrix::MakeFromX(Target->GetActorLocation() - GetActorLocation()).Rotator();
				GetWorld()->SpawnActor<ADroneGameProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
			}
		}
		// Set a timer to fire again
		GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &ATurretActor::ResetFire, 1 / fireRate, true);
		bCanFire = false;
	}
}

void ATurretActor::ResetFire()
{
	bCanFire = true;
	GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
	Fire();
}

// Called every frame
void ATurretActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(Target){
		FRotator LookAtRotation = FRotationMatrix::MakeFromX(Target->GetActorLocation() - GetActorLocation()).Rotator();
		FRotator CurrentRotation = TurretMesh->GetComponentRotation();
		FRotator NewRotation = FMath::RInterpTo(CurrentRotation, LookAtRotation, DeltaTime, 5.0f);
		TurretMesh->SetWorldRotation(NewRotation);
	}

}

void ATurretActor::OnComponentBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if(OtherActor){
		if(Cast<ADronePawn>(OtherActor)){
			Target = Cast<ADronePawn>(OtherActor);
			Fire();
		}
	}
}

void ATurretActor::OnComponentEndOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex)
{
	if(OtherActor){
		if(Target == Cast<ADronePawn>(OtherActor)){
			Target = nullptr;
		}
	}
}

void ATurretActor::Damage(int32 DamageAmount)
{
	Health -= DamageAmount;
	if (Health <= 0)
	{
		Destroy();
	}
}

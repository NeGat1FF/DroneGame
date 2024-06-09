// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageableInterface.h"
#include "TurretActor.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class ADroneGameProjectile;
class ADronePawn;

UCLASS()
class DRONEGAME_API ATurretActor : public AActor, public IDamageableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurretActor();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Mesh)
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Collision)
	USphereComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	TSubclassOf<class ADroneGameProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret")
	float fireRate = 1.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Fire();
	void ResetFire();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);

	virtual void Damage(int32 DamageAmount) override;

private:
	float Health = 100.0f;

	ADronePawn* Target = nullptr;

	FTimerHandle FireTimerHandle;

	bool bCanFire = true;

};

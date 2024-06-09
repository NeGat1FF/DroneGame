// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupInterface.h"
#include "BasePickupItem.generated.h"

class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class DRONEGAME_API ABasePickupItem : public AActor, public IPickupInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasePickupItem();

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	UStaticMeshComponent *MeshComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Collision")
	USphereComponent *CollisionComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float RotationSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float LevitationAmplitude;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float LevitationSpeed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnPickup(class AActor *ActorThatPickedUp) override;

private:
	float RunningTime;

};

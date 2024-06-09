// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnPickableItemsActor.generated.h"

class ABasePickupItem;
class UBoxComponent;

UCLASS()
class DRONEGAME_API ASpawnPickableItemsActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnPickableItemsActor();

	UPROPERTY(EditAnywhere, Category = "Spawn bounds")
	UBoxComponent* SpawnBounds;

	UPROPERTY(EditAnywhere, Category = "Spawn items")
	TArray<TSubclassOf<ABasePickupItem>> PickupItemClasses;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Called when the game starts or when spawned
	FTimerHandle TimerHandle;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void SpawnPickupItem();

};

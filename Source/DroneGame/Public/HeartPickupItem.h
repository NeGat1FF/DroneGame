// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePickupItem.h"
#include "HeartPickupItem.generated.h"

/**
 * 
 */
UCLASS()
class DRONEGAME_API AHeartPickupItem : public ABasePickupItem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Health")
	int HealthAmount = 10;

	virtual void OnPickup(class AActor *ActorThatPickedUp) override;
	
};

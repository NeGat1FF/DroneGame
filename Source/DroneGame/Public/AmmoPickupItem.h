// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePickupItem.h"
#include "AmmoPickupItem.generated.h"

/**
 * 
 */
UCLASS()
class DRONEGAME_API AAmmoPickupItem : public ABasePickupItem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Ammo")
	int AmmoAmount = 10;

	virtual void OnPickup(class AActor *ActorThatPickedUp) override;
	
};

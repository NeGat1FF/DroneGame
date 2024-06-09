// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DroneHUDWidget.generated.h"

class UProgressBar;
class UTextBlock;
/**
 *
 */
UCLASS()
class DRONEGAME_API UDroneHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// Updates the health display
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void UpdateHealth(float Health, float MaxHealth);

	// Updates the ammo display
	UFUNCTION(BlueprintCallable, Category = "HUD")
	void UpdateAmmo(int32 Ammo, int32 MaxAmmo);

private:
	// Health text
	UPROPERTY(meta = (BindWidget))
	class UProgressBar *HealthBar;

	// Ammo text
	UPROPERTY(meta = (BindWidget))
	class UTextBlock *AmmoText;
};

// Fill out your copyright notice in the Description page of Project Settings.

#include "DroneHUDWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UDroneHUDWidget::UpdateHealth(float Health, float MaxHealth)
{
    if (HealthBar)
    {
        HealthBar->SetPercent(Health / MaxHealth);
    }
}

void UDroneHUDWidget::UpdateAmmo(int32 Ammo, int32 MaxAmmo)
{
    if (AmmoText)
    {
        AmmoText->SetText(FText::FromString(FString::Printf(TEXT("Ammo: %d/%d"), Ammo, MaxAmmo)));
    }
}
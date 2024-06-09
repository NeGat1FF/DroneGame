// Fill out your copyright notice in the Description page of Project Settings.


#include "HeartPickupItem.h"
#include "DronePawn.h"

void AHeartPickupItem::OnPickup(AActor *ActorThatPickedUp)
{
    if(ADronePawn *DronePawn = Cast<ADronePawn>(ActorThatPickedUp))
    {
        if(DronePawn->GetHealth() < DronePawn->GetMaxHealth())
        {
            DronePawn->AddHealth(HealthAmount);

            Super::OnPickup(ActorThatPickedUp);
        }
    }
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoPickupItem.h"
#include "DronePawn.h"

void AAmmoPickupItem::OnPickup(AActor *ActorThatPickedUp)
{
    if(ADronePawn *DronePawn = Cast<ADronePawn>(ActorThatPickedUp))
    {
        if(DronePawn->GetAmmo() < DronePawn->GetMaxAmmo())
        {
            DronePawn->AddAmmo(AmmoAmount);

            Super::OnPickup(ActorThatPickedUp);
        }
    }
}

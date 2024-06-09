// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnPickableItemsActor.h"
#include "Components/BoxComponent.h"
#include "BasePickupItem.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ASpawnPickableItemsActor::ASpawnPickableItemsActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SpawnBounds = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBounds"));
	RootComponent = SpawnBounds;
	SpawnBounds->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called when the game starts or when spawned
void ASpawnPickableItemsActor::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle, this, &ASpawnPickableItemsActor::SpawnPickupItem, 30.0f, true, 0.0f);
}

// Called every frame
void ASpawnPickableItemsActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpawnPickableItemsActor::SpawnPickupItem()
{
	if(PickupItemClasses.Num() > 0){
		FVector SpawnLocation = UKismetMathLibrary::RandomPointInBoundingBox(SpawnBounds->GetComponentLocation(), SpawnBounds->GetScaledBoxExtent());
		int32 RandomIndex = FMath::RandRange(0, PickupItemClasses.Num() - 1);
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
		GetWorld()->SpawnActor<ABasePickupItem>(PickupItemClasses[RandomIndex], SpawnLocation, FRotator::ZeroRotator, SpawnParams);
	}

	GetWorldTimerManager().SetTimer(TimerHandle, this, &ASpawnPickableItemsActor::SpawnPickupItem, FMath::RandRange(25.0f,30.0f), false, 30.0f);
}


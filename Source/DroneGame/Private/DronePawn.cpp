// Fill out your copyright notice in the Description page of Project Settings.

#include "DronePawn.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Blueprint/UserWidget.h"
#include "PickupInterface.h"
#include "DroneGameProjectile.h"
#include "DroneHUDWidget.h"

// Sets default values
ADronePawn::ADronePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;
	BoxComponent->SetCollisionProfileName(TEXT("Pawn"));

	DroneCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("DroneCamera"));
	DroneCamera->SetupAttachment(BoxComponent);
	DroneCamera->bUsePawnControlRotation = true;

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
	MovementComponent->UpdatedComponent = BoxComponent;
	MovementComponent->MaxSpeed = 1000.f;
	MovementComponent->Acceleration = 1000.f;
	MovementComponent->Deceleration = 500.f;

	MovementComponent->NavAgentProps.bCanFly = true;

	bUseControllerRotationYaw = true;
}

// Called when the game starts or when spawned
void ADronePawn::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController *PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem *Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (HUDWidgetClass)
	{
		HUDWidget = CreateWidget<UDroneHUDWidget>(GetWorld(), HUDWidgetClass);
		if (HUDWidget)
		{
			HUDWidget->AddToViewport();
			HUDWidget->UpdateHealth(Health, MaxHealth);
			HUDWidget->UpdateAmmo(Ammo, MaxAmmo);
		}
	}

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ADronePawn::OnComponentBeginOverlap);
}

// Called every frame
// void ADronePawn::Tick(float DeltaTime)
// {
// 	Super::Tick(DeltaTime);

// }

// Called to bind functionality to input
void ADronePawn::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent *EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADronePawn::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ADronePawn::Look);

		// Lifting
		EnhancedInputComponent->BindAction(LiftAction, ETriggerEvent::Triggered, this, &ADronePawn::Lift);

		// Shooting
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &ADronePawn::Shoot);
	}
}

int ADronePawn::GetHealth() const
{
	return Health;
}

int ADronePawn::GetAmmo() const
{
	return Ammo;
}

int ADronePawn::GetMaxHealth() const
{
	return MaxHealth;
}

int ADronePawn::GetMaxAmmo() const
{
	return MaxAmmo;
}

void ADronePawn::AddHealth(int Value)
{
	Health = FMath::Clamp(Health + Value, 0, MaxHealth);

	if (HUDWidget)
	{
		HUDWidget->UpdateHealth(Health, MaxHealth);
	}
}

void ADronePawn::AddAmmo(int Value)
{
	Ammo = FMath::Clamp(Ammo + Value, 0, MaxAmmo);

	if (HUDWidget)
	{
		HUDWidget->UpdateAmmo(Ammo, MaxAmmo);
	}
}

void ADronePawn::Damage(int DamageAmount)
{
	if (DamageAmount > 0)
	{
		Health = FMath::Clamp(Health - DamageAmount, 0, MaxHealth);
	}

	if (HUDWidget)
	{
		HUDWidget->UpdateHealth(Health, MaxHealth);
	}
}

void ADronePawn::Move(const FInputActionValue &Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	AddMovementInput(GetActorForwardVector(), MovementVector.X);
	AddMovementInput(GetActorRightVector(), MovementVector.Y);
}

void ADronePawn::Look(const FInputActionValue &Value)
{
	FVector2D LookVector = Value.Get<FVector2D>();

	AddControllerYawInput(LookVector.X);
	AddControllerPitchInput(-LookVector.Y);
}

void ADronePawn::Lift(const FInputActionValue &Value)
{
	float LiftValue = Value.Get<float>();

	AddMovementInput(GetActorUpVector(), LiftValue);
}

void ADronePawn::Shoot(const FInputActionValue &Value)
{
	if (ProjectileClass)
	{
		UWorld *const World = GetWorld();
		if (World)
		{
			if (Ammo > 0)
			{
				Ammo--;

				FVector SpawnLocation = DroneCamera->GetComponentLocation() + DroneCamera->GetForwardVector() * 100.0f;
				FRotator SpawnRotation = DroneCamera->GetComponentRotation();

				FActorSpawnParameters ActorSpawnParams;
				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

				World->SpawnActor<ADroneGameProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
			}
		}
	}

	if (HUDWidget)
	{
		HUDWidget->UpdateAmmo(Ammo, MaxAmmo);
	}
}

void ADronePawn::OnComponentBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor->Implements<UPickupInterface>())
	{
		Cast<IPickupInterface>(OtherActor)->OnPickup(this);
	}
}

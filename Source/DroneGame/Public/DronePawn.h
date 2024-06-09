// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DamageableInterface.h"
#include "DronePawn.generated.h"

class UBoxComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UFloatingPawnMovement;
class UDroneHUDWidget;
class ADroneGameProjectile;
struct FInputActionValue;

UCLASS()
class DRONEGAME_API ADronePawn : public APawn, public IDamageableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADronePawn();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Root)
	UBoxComponent* BoxComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Camera)
	UCameraComponent* DroneCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input|Input Actions")
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input|Input Actions")
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input|Input Actions")
	UInputAction* LiftAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input|Input Actions")
	UInputAction* ShootAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	UFloatingPawnMovement* MovementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<ADroneGameProjectile> ProjectileClass;

private:

	// Health
	UPROPERTY(EditDefaultsOnly, Category = "Health", meta = (AllowPrivateAccess = "true"))
	int MaxHealth = 100;

	UPROPERTY(VisibleInstanceOnly, Category = "Health")
	int Health = 100;

	// Ammo
	UPROPERTY(EditDefaultsOnly, Category = "Ammo", meta = (AllowPrivateAccess = "true"))
	int MaxAmmo = 64;

	UPROPERTY(VisibleInstanceOnly, Category = "Ammo")
	int Ammo = 64;

	UPROPERTY()
	class UDroneHUDWidget* HUDWidget;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	// virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	int GetHealth() const;

	UFUNCTION(BlueprintCallable)
	int GetAmmo() const;

	UFUNCTION(BlueprintCallable)
	int GetMaxHealth() const;

	UFUNCTION(BlueprintCallable)
	int GetMaxAmmo() const;

	UFUNCTION(BlueprintCallable)
	void AddHealth(int Value);

	UFUNCTION(BlueprintCallable)
	void AddAmmo(int Value);

	virtual void Damage(int DamageAmount) override;

private:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Lift(const FInputActionValue& Value);
	void Shoot(const FInputActionValue& Value);

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};

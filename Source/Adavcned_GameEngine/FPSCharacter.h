// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "InventorySystem.h"
#include "Pickup.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"
#include "Enemy.h"
//---------------------------------------------
#include "FPSCharacter.generated.h"

UCLASS()
class ADAVCNED_GAMEENGINE_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Handles input for moving forward and backward.
	UFUNCTION()
		void MoveForward(float Value);

	// Handles input for moving right and left.
	UFUNCTION()
		void MoveSideways(float Value);

	// Sets jump flag when key is pressed.
	UFUNCTION()
		void StartJump();

	// Clears jump flag when key is released.
	UFUNCTION()
		void StopJump();

	// Function that handles firing projectiles.
	UFUNCTION()
		void Shoot();

	// Function that handles sucking the projectiles.
	UFUNCTION()
		void Suck();

	UFUNCTION()
		void Pickup();

	UPROPERTY(EditAnywhere)
		class USceneComponent* HoldingComponent;

	// FPS camera.
	UPROPERTY(VisibleAnywhere)
		UCameraComponent* FPSCameraComponent;

	// First-person mesh (arms), visible only to the owning player.
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		USkeletalMeshComponent* FPSMesh;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* ShootPoint;


	// Gun muzzle offset from the camera location.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun")
		FVector MuzzleOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun")
		int32 GunDistance = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EffectSystem")
		UParticleSystem* Effect;

	UPROPERTY(VisibleDefaultsOnly, Category = "Inventory")
		UActorComponent* Inventory;

	UPROPERTY(EditAnywhere)
		class APickup* CurrentPickup;


	bool bCanMove;
	bool bHoldingItem;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun")
		int32 SuctionRadius = 500;

	

};

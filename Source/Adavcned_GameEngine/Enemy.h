// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "TimerManager.h"
#include "InventorySystem.h"
#include "FPSCharacter.h"
#include "Item.h"
#include "Enemy.generated.h"

UCLASS()
class ADAVCNED_GAMEENGINE_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		bool bIsSkeletalMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ID")
		FString ID;

	UPROPERTY()
		bool CanSuck = false;
	UPROPERTY()
		FVector Location;
	UPROPERTY()
		FVector SpawnLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Respawn")
		FTimerHandle RespawnTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Respawn")
		float Timer = 6;

	UPROPERTY()
	bool bIsEnabled = true;

	UPROPERTY()
		class AFPSCharacter* Player;

	UFUNCTION()
	void SuckIn();

	UFUNCTION()
	void Respawn();

	// Function that is called when the projectile hits something.
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Bomb.generated.h"

UCLASS()
class ADAVCNED_GAMEENGINE_API ABomb : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABomb();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	int32 BlastRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blast")
		FTimerHandle BlastTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blast")
		float Timer = 2;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Mesh")
		UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly, Category = "Collision")
		USphereComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EffectSystem")
		UNiagaraSystem* Effect;

	// Create Event
	UFUNCTION(BlueprintImplementableEvent, Category = "Explode")
		void OnExplode();

	bool bFlag = false;
	

	void Explode();

};

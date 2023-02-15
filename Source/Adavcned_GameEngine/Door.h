// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Adavcned_GameEngineGameModeBase.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

UCLASS()
class ADAVCNED_GAMEENGINE_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Door")
		float TargetHeight = 20;
	UPROPERTY(EditAnywhere, Category = "Door")
		float MoveSpeed;

	UPROPERTY(EditAnywhere, Category = "Door")
		int32 SlimeAmount;

	FVector CurrentLocation;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
		UStaticMeshComponent* Mesh;

	bool bDoorOpened;

	UFUNCTION()
		void OpenDoor(float DeltaTime);
};

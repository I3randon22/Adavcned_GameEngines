// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerVolume.h"
#include "FPSCharacter.h"
#include "TriggerPlatform.generated.h"

UENUM(BlueprintType)
enum class Direction : uint8
{
	X = 0   UMETA(DisplayName = "XAxis"),
	Y = 1   UMETA(DisplayName = "YAxis"),
	Z = 2   UMETA(DisplayName = "ZAxis")
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ADAVCNED_GAMEENGINE_API ATriggerPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATriggerPlatform();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "Door")
		Direction direction = Direction::Z;
	UPROPERTY(EditAnywhere, Category = "Door")
		float TargetHeightStart = 20;
	UPROPERTY(EditAnywhere, Category = "Door")
		float MoveSpeed;
	UPROPERTY(EditAnywhere, Category = "Trigger")
		ATriggerVolume* TriggerVol;

	UPROPERTY(EditAnywhere, Category = "Door")
		bool bReturn = true;
	UPROPERTY(EditAnywhere, Category = "Door")
		bool bCloseOnExit = true;

	UPROPERTY()
		FVector CurrentLocation;
	UPROPERTY()
		float StartHeight;
	UPROPERTY()
		float TargetHeight;
	UPROPERTY()
		bool bIsClosing = false;


	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
		void OpenDoor(float DeltaTime, float Height);
	UFUNCTION()
		void GetAllValidActors(float DeltaTime);




};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "Adavcned_GameEngineGameModeBase.h"
#include "Enemy.h"
#include "SlimeTriggerBox.generated.h"

/**
 * 
 */
UCLASS()
class ADAVCNED_GAMEENGINE_API ASlimeTriggerBox : public ATriggerBox
{
	GENERATED_BODY()

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:

	// constructor sets default values for this actor's properties
	ASlimeTriggerBox();

	// declare overlap begin function
	UFUNCTION()
		void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	// declare overlap end function
	UFUNCTION()
		void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);

	
};

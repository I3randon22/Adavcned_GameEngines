// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Item.h"
#include "ItemData.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy.h"
#include "Adavcned_GameEngineGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ADAVCNED_GAMEENGINE_API AAdavcned_GameEngineGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	virtual void StartPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory System")
		class UItemData* ItemDatabase;

public:

	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Inventory System")
	FItem FindItem(FString ID, bool& Success);

	FItem FindItem_Implementation(FString ID, bool& Success);

	void CheckSlimes();

	void CheckSlimesAmount();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Slime")
		int32 SlimeCounter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Slime")
		int32 SlimeCounterMax;

	bool bGameComplete;
		
};



#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemData.h"
#include "Item.h"
#include "FPSCharacter.h"
#include "Adavcned_GameEngineGameModeBase.h"
#include "InventorySystem.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ADAVCNED_GAMEENGINE_API UInventorySystem : public UActorComponent
{
	GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
        TArray<FItem> Inventory;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
        int32 Slots = 4;

public:	
    UFUNCTION(BlueprintCallable, Category = "Inventory")
        bool AddItem(FString ID);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
        bool RemoveItem(FString ID);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
        TArray<FItem> GetInventoryItems();

    UFUNCTION(BlueprintCallable, Category = "Inventory")
        FItem GetCurrentItem(bool& Success);

    //UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
       // UItemData* InventoryItems;

    UFUNCTION(BlueprintCallable, Category = "Events")
        void RefreshInventory();

		
};

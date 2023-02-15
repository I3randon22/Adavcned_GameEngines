// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySystem.h"
#include "Adavcned_GameEngineGameModeBase.h"

bool UInventorySystem::AddItem(FString ID)
{
    //Check if the inventory is full
    if (Inventory.Num() < Slots)
    {
        //Iterate through the items in the inventory
        for (int i = 0; i < Inventory.Num(); i++)
        {
            //Check if the current item's ID matches the ID of the item being added
            if (Inventory[i].ID == ID)
            {
                //If a match is found, increase the quantity of the item
                Inventory[i].Quantity += 1;

                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("ItemAdded"));

                //Refresh the inventory
                RefreshInventory();

                //Return true to indicate that the item was added successfully
                return true;
            }
        }

        //Get a reference to the game mode
        AAdavcned_GameEngineGameModeBase* GameMode = Cast<AAdavcned_GameEngineGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode != nullptr)
        {
            //Check if the item exists
            bool Found = false;
            FItem ItemFound = GameMode->FindItem_Implementation(ID, Found);

            //If the item exists, add it to the inventory
            if (Found)
            {
                FItem NewItem;
                NewItem.ItemName = ItemFound.ItemName;
                NewItem.ID = ItemFound.ID;
                NewItem.Description = ItemFound.Description;
                NewItem.Quantity = 1;
                NewItem.Icon = ItemFound.Icon;
                NewItem.ItemActor = ItemFound.ItemActor;
                NewItem.LaunchPower = ItemFound.LaunchPower;
                NewItem.bStack = ItemFound.bStack;

                Inventory.Add(NewItem);

                //Add a debug message to the screen
                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("ItemFound"));

                //Refresh the inventory
                RefreshInventory();

                //Return true to indicate that the item was added successfully
                return true;
            }

            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Item Doesn't Exist"));

            //Return false to indicate that the item was not added
            return false;
        }
    }
    else
    {
        //If the inventory is full, add a debug message to the screen
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("InventoryFull"));

        //Return false to indicate that the item was not added
        return false;
    }

    //Return false as a default case
    return false;

}

bool UInventorySystem::RemoveItem(FString ID)
{
    //Iterate through inventory
    for (int i = 0; i < Inventory.Num(); i++)
    {
        //If Item ID Matches
        if (Inventory[i].ID == ID)
        {
            //Decrease quantity of item
            Inventory[i].Quantity -= 1;
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("ItemDepleted"));

            //If quantity of item is smaller or equal to 0 remove it from inventory
            if (Inventory[i].Quantity <= 0) 
            {
                Inventory.RemoveAt(i);
                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("ItemRemoved"));
            }
            //Refresh Inventory
            RefreshInventory();
            //Return true to indicate item was successfully removed
            return true;
        }
    }
    //return false to indicate item was unsuccessfully removed
    return false;
}

TArray<FItem> UInventorySystem::GetInventoryItems()
{
	return TArray<FItem>();
}

FItem UInventorySystem::GetCurrentItem(bool& Success)
{
    FItem Item;
    //If inventory has an item stored return it
    if (Inventory.Num() > 0)
    {
        Success = true;
        return Inventory[0];
    }
    //return a default item and indicate it was unsuccessful
    Success = false;
    return Item;

}

void UInventorySystem::RefreshInventory()
{

}

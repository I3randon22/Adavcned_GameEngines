#include "Adavcned_GameEngineGameModeBase.h"

void AAdavcned_GameEngineGameModeBase::StartPlay()
{
	Super::StartPlay();

	SlimeCounter = 0;
	CheckSlimes();

}

FItem AAdavcned_GameEngineGameModeBase::FindItem(FString ID, bool& Success)// For Inventory UI
{
	return FItem();
}


FItem AAdavcned_GameEngineGameModeBase::FindItem_Implementation(FString ID, bool& Success)
{
	Success = false;

	FItem Item;
	if (ItemDatabase == nullptr) { return Item;  }

	for (int i = 0; i < ItemDatabase->Data.Num(); i++)
	{
		if (ItemDatabase->Data[i].ID == ID)
		{
			Success = true;
			return ItemDatabase->Data[i];
		}
	}

	return Item;
}

void AAdavcned_GameEngineGameModeBase::CheckSlimes()
{
	//Get a list of all actors within radius
	TArray<AActor*> actorsInRadius;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), actorsInRadius);

	for (auto actor : actorsInRadius)
	{
		if (Cast<AEnemy>(actor)->ID == "01")
		{
			SlimeCounterMax++;
		}

	}
}

void AAdavcned_GameEngineGameModeBase::CheckSlimesAmount()
{
	if (SlimeCounter >= SlimeCounterMax)
	{
		bGameComplete = true;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Game Complete!"));
	}
}

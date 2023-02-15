// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.generated.h"

USTRUCT(BlueprintType)
struct FItem
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
        FString ItemName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
        FString ID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
        FString Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
        TSubclassOf<class AActor> ItemActor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
        UTexture2D* Icon;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
        int32 Quantity;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
        bool bStack;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
        int32 LaunchPower;
};

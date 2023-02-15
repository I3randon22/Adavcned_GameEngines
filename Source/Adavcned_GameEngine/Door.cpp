// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	CurrentLocation = GetActorLocation();
	TargetHeight += CurrentLocation.Z;
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bDoorOpened)
	{
		AAdavcned_GameEngineGameModeBase* GameMode = Cast<AAdavcned_GameEngineGameModeBase>(GetWorld()->GetAuthGameMode());

		if (GameMode != nullptr)
		{
			if (GameMode->SlimeCounter >= SlimeAmount)
			{
				OpenDoor(DeltaTime);
			}
		}
	}

}

void ADoor::OpenDoor(float DeltaTime)
{
	CurrentLocation.Z = FMath::FInterpConstantTo(CurrentLocation.Z, TargetHeight, DeltaTime, MoveSpeed);
	SetActorLocation(CurrentLocation);

	/*if (CurrentLocation.Z == TargetHeight)
	{
		bDoorOpened = true;
	}*/
}


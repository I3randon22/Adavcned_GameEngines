// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerPlatform.h"

// Sets default values
ATriggerPlatform::ATriggerPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void ATriggerPlatform::BeginPlay()
{
	Super::BeginPlay();
	CurrentLocation = GetActorLocation();
	

	switch (direction)
	{
	case Direction::X:
		StartHeight = CurrentLocation.X;
		TargetHeightStart += CurrentLocation.X;
		break;
	case Direction::Y:
		StartHeight = CurrentLocation.Y;
		TargetHeightStart += CurrentLocation.Y;
		break;
	case Direction::Z:
		StartHeight = CurrentLocation.Z;
		TargetHeightStart += CurrentLocation.Z;
		break;
	default:
		break;
	}

	TargetHeight = TargetHeightStart;
}

// Called every frame
void ATriggerPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GetAllValidActors(DeltaTime);
}

void ATriggerPlatform::GetAllValidActors(float DeltaTime)
{
	if (TriggerVol == nullptr) return;
		
		
	if (TriggerVol->IsOverlappingActor(GetWorld()->GetFirstPlayerController()->GetPawn())) TargetHeight = TargetHeightStart;
	else if (bCloseOnExit) TargetHeight = StartHeight;

	if (!bCloseOnExit)
	{
		if (bReturn)
		{
			TargetHeight = StartHeight;
		}
		else
		{
			TargetHeight = TargetHeightStart;
		}
		
	}

	OpenDoor(DeltaTime, TargetHeight);
}

void ATriggerPlatform::OpenDoor(float DeltaTime, float Height)
{
	switch (direction)
	{
	case Direction::X:
		if (CurrentLocation.X == Height) bReturn = true; 
		if (CurrentLocation.X == StartHeight) bReturn = false;
		CurrentLocation.X = FMath::FInterpConstantTo(CurrentLocation.X, Height, DeltaTime, MoveSpeed);
		break;
	case Direction::Y:
		if (CurrentLocation.Y == Height) bReturn = true;
		if (CurrentLocation.Y == StartHeight) bReturn = false;
		CurrentLocation.Y = FMath::FInterpConstantTo(CurrentLocation.Y, Height, DeltaTime, MoveSpeed);
		break;
	case Direction::Z:
		if (CurrentLocation.Z == Height) bReturn = true;
		if (CurrentLocation.Z == StartHeight) bReturn = false;
		CurrentLocation.Z = FMath::FInterpConstantTo(CurrentLocation.Z, Height, DeltaTime, MoveSpeed);
		break;
	default:
		break;
	}

	SetActorRelativeLocation(CurrentLocation);
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"

// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	RootComponent = Mesh;
	bHolding = false;
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
	AFPSCharacter* Player = Cast<AFPSCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	PlayerCamera = Player->FPSCameraComponent;
	TArray<USceneComponent*> Components;

	Player->GetComponents(Components);

	if (Components.Num() > 0)
	{
		for (auto& Comp : Components)
		{
			if (Comp->GetName() == "HoldingComponent")
			{
				HoldingComp = Cast<USceneComponent>(Comp);
			}
		}
	}
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bHolding && HoldingComp)
	{
		SetActorLocationAndRotation(HoldingComp->GetComponentLocation(), HoldingComp->GetComponentRotation());
	}
}

void APickup::PickupActor()
{
	bHolding = !bHolding;

	Mesh->SetSimulatePhysics(bHolding ? false : true);
	Mesh->SetCollisionEnabled(bHolding ? ECollisionEnabled::NoCollision : ECollisionEnabled::QueryAndPhysics);

	if (bHolding && Mesh->IsSimulatingPhysics())
	{
		AFPSCharacter* Player = Cast<AFPSCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
		FVector ForwardVector = PlayerCamera->GetForwardVector();
		Mesh->AddForce(ForwardVector * 100000 * Mesh->GetMass());
	}
}


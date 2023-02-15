// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
		RootComponent = Mesh;
	}

	Mesh->SetSimulatePhysics(true);
	bIsEnabled = true;

	ID = "01";
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<AFPSCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	SpawnLocation = GetActorLocation();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CanSuck && bIsEnabled && Player)
	{
		//Move Actor towards gun muzzle
		FVector MuzzleLocation = Player->ShootPoint->GetComponentLocation();

		FVector Direction = ((MuzzleLocation - GetActorLocation())).GetSafeNormal();
		FVector NewLocation = GetActorLocation() + Direction * 1000 * DeltaTime;

		SetActorLocation(NewLocation);

		//Move skeletal mesh towards gun muzzle if exists
		if (bIsSkeletalMesh)
		{
			USkeletalMeshComponent* SkeletalMesh = FindComponentByClass<USkeletalMeshComponent>();
			FVector SkeletalMeshLocation = SkeletalMesh->GetComponentLocation();

			Direction = ((MuzzleLocation - SkeletalMeshLocation)).GetSafeNormal();
			NewLocation = SkeletalMeshLocation + Direction * 1300 * DeltaTime;

			SkeletalMesh->SetWorldLocation(NewLocation, false, nullptr, ETeleportType::TeleportPhysics);
			SetActorLocation(SkeletalMesh->GetComponentLocation());
		}

		//When actor is close enough to muzzle addd it to inventory and destroy it
		if (FVector::Dist(GetActorLocation(), MuzzleLocation) <= 30)
		{
			UInventorySystem* Inventory = Cast<UInventorySystem>(Player->Inventory);

			if (Inventory != nullptr)
			{
				if (Inventory->AddItem(ID))
				{
					if (ID == "02") //If is bomb respawn
					{
						SetActorHiddenInGame(true);
						bIsEnabled = false;
						CanSuck = false;
						Mesh->SetSimulatePhysics(false);
						Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
						GetWorld()->GetTimerManager().SetTimer(RespawnTimer, this, &AEnemy::Respawn, Timer, false);
					}
					else
					{
						Destroy();
					}

				}
			}

		}
		
	}
}

//When the enemy hits something, add force to the object hit
void AEnemy::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	{
		OtherComponent->AddImpulseAtLocation(Mesh->GetPhysicsLinearVelocity() * 5000.0f, Hit.ImpactPoint);
	}
}

void AEnemy::SuckIn()
{
	
	//Set Simulate Physics depending on if if item is being sucked into gun
	if (!CanSuck)
	{
		Mesh->SetSimulatePhysics(false);
		CanSuck = true;
	}
	else
	{
		Mesh->SetSimulatePhysics(true);
		CanSuck = false;
	}
}

void AEnemy::Respawn()
{
	bIsEnabled = true;
	CanSuck = false;
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetSimulatePhysics(true);
	SetActorLocation(SpawnLocation);
	SetActorHiddenInGame(false);
}


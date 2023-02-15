// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	}

	if (!CollisionComponent)
	{
		//Sphere collision Set
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		CollisionComponent->SetSimulatePhysics(true);
		//SetActorEnableCollision(false);
		//Collision radius.
		CollisionComponent->InitSphereRadius(15.0f);

		// Set root to be the collision
		RootComponent = CollisionComponent;
	}

	if (!ProjectileMovementComponent)
	{
		//projectile's movement.
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
		ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
		ProjectileMovementComponent->InitialSpeed = 1000.0f;
		ProjectileMovementComponent->MaxSpeed = 3000.0f;
		ProjectileMovementComponent->bRotationFollowsVelocity = true;
		ProjectileMovementComponent->bShouldBounce = true;
		ProjectileMovementComponent->Bounciness = 0.8f;
		ProjectileMovementComponent->ProjectileGravityScale = 100.0f;
	}

	if (!ProjectileMeshComponent)
	{
		//Create and set mesh of projectile
		ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("StaticMesh'/Game/Mesh/Sphere/Sphere.Sphere'"));
		if (Mesh.Succeeded())
		{
			ProjectileMeshComponent->SetStaticMesh(Mesh.Object);
		}

		//Create and set material for mesh
		static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("Material'/Game/Mesh/Sphere/SphereMat.SphereMat'"));
		if (Material.Succeeded())
		{
			ProjectileMat = UMaterialInstanceDynamic::Create(Material.Object, ProjectileMeshComponent);
		}
		ProjectileMeshComponent->SetMaterial(0, ProjectileMat);
		ProjectileMeshComponent->SetRelativeScale3D(FVector(0.09f, 0.09f, 0.09f));
		ProjectileMeshComponent->SetupAttachment(RootComponent);
	}

	// Delete the projectile after 3 seconds.
	//InitialLifeSpan = 300.0f;

	// Set the sphere's collision to "Projectile".
	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));

	// Event called when projectile collision hits something.
	CollisionComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);


	ItemName = "TestTwo"; //Change to do in blueprints
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// get first player pawn location

	if (CanSuck)
	{
		AFPSCharacter* Player = Cast<AFPSCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
		FVector PlayerLocation = Player->GetActorLocation();
		FVector Direction = ((PlayerLocation - GetActorLocation()) + (FVector::ZAxisVector * 250)).GetSafeNormal();
		FVector NewLocation = GetActorLocation() + Direction  * 1000 * DeltaTime;
		SetActorLocation(NewLocation);

		if (FVector::Dist(GetActorLocation(), PlayerLocation) <= 200)
		{
			UInventorySystem* Inventory = Cast<UInventorySystem>(Player->Inventory);

			if (Inventory != nullptr)
			{
				if(Inventory->AddItem(ItemName))//If 
				{
					Destroy();
				}
				
			}
			
		}
	}
}

//shoot direction. Called inside FPSCharacter
void AProjectile::ShootInDirection(const FVector& Direction)
{	
	ProjectileMovementComponent->Velocity = Direction * ProjectileMovementComponent->InitialSpeed;
}

//When the projectile hits something, add force to the object hit
void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	{
		OtherComponent->AddImpulseAtLocation(ProjectileMovementComponent->Velocity * 50.0f, Hit.ImpactPoint);
	}

	//Destroy();
}

void AProjectile::SuckIn(FVector& Muzzle)
{
	// Disable the actor so it can't be picked up again
	

	//SetActorHiddenInGame(true);
	Location = Muzzle;
	if (!CanSuck)
	{
		//SetActorEnableCollision(false);
		CanSuck = true;
	}
	else
	{
		//SetActorEnableCollision(true);
		CanSuck = false;
	}
	
}


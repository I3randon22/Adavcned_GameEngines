#include "Bomb.h"

ABomb::ABomb()
{
    PrimaryActorTick.bCanEverTick = true;

    //Create default scene component as the root component
    if (!RootComponent)
    {
        RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("BombSceneComponent"));
    }

    //Create static mesh component
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    //Create sphere component for collision
    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));

    //Attach mesh and collision components to the root component
    Mesh->SetupAttachment(RootComponent);
    CollisionComponent->SetupAttachment(Mesh);

    //Set physics simulation for the mesh component
    Mesh->SetSimulatePhysics(true);
}

//Called when the game starts or when spawned
void ABomb::BeginPlay()
{
    Super::BeginPlay();
    //Set a timer to trigger the explosion
    GetWorld()->GetTimerManager().SetTimer(BlastTimer, this, &ABomb::Explode, Timer, false);
}

//Called every frame
void ABomb::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

//Function to explode the bomb
void ABomb::Explode()
{
    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Explode"));

    //If effect is valid and not already played
    if (Effect->IsValid() && !bFlag)
    {
        //Spawn the effect at the location of the mesh component
        UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Effect, Mesh->GetRelativeLocation());
        OnExplode();
        bFlag = true;
        //Reset timer
        Timer = 1;
        //Destroy the mesh component
        Mesh->DestroyComponent();
        //Set the timer again
        GetWorld()->GetTimerManager().SetTimer(BlastTimer, this, &ABomb::Explode, Timer, false);
    }
    else
    {
        //Destroy the actor
        Destroy();
    }
}

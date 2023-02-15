// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a first person camera component.
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	check(FPSCameraComponent != nullptr);

	// Attach the camera component to our capsule component.
	FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));

	// Position the camera 50 above the eyes
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));

	// Enable the pawn to control camera rotation.
	FPSCameraComponent->bUsePawnControlRotation = true;

	// Create a first person mesh component for the arms of player.
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	check(FPSMesh != nullptr);

	// Only the owning player sees this mesh.
	FPSMesh->SetOnlyOwnerSee(true);

	// Attach the FPS mesh to the FPS camera.
	FPSMesh->SetupAttachment(FPSCameraComponent);

	//Turn off shadows for mesh
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;

	//The owning player doesn't see the body mesh.
	GetMesh()->SetOwnerNoSee(true);

	Inventory = CreateDefaultSubobject<UInventorySystem>(TEXT("InventorySystem"));
	check(Inventory != nullptr);

	//Create a first person mesh component for the arms of player.
	ShootPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ShootPoint"));
	//check(ShootPoint != nullptr);

	// Attach the Gun mesh to the FPS camera.
	ShootPoint->AttachToComponent(FPSCameraComponent, FAttachmentTransformRules::KeepRelativeTransform, "Muzzle");

	//Pickup Objects
	HoldingComponent = CreateDefaultSubobject<USceneComponent>(TEXT("HoldingComponent"));
	HoldingComponent->SetRelativeLocation(FVector(50.0f, HoldingComponent->GetRelativeLocation().Y, HoldingComponent->GetRelativeLocation().Z));
	HoldingComponent->SetupAttachment(ShootPoint);

	CurrentPickup = nullptr;
	bCanMove = true;
	
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();	


}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	

	if (!bHoldingItem)
	{
		//RayCast Line 
		FVector Start = FPSCameraComponent->GetComponentLocation();
		FVector ForwardVector = FPSCameraComponent->GetForwardVector();
		FVector End = ((ForwardVector * 300.f) + Start); //Distance set to 200 can change

		FHitResult Hit;
		FComponentQueryParams DefaultComponentQueryParams;
		FCollisionResponseParams DefaultResponseParam;

		if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, DefaultComponentQueryParams, DefaultResponseParam))
		{
 			if(Hit.GetActor()->GetClass()->IsChildOf(APickup::StaticClass())) 
			{
				CurrentPickup = Cast<APickup>(Hit.GetActor());
			}
		}
		else
		{
			CurrentPickup = nullptr;
		}
	}

	if (bHoldingItem)
	{
		HoldingComponent->SetRelativeLocation(FVector(170, 0, 0));
	}
}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up "movement" bindings.
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveSideways", this, &AFPSCharacter::MoveSideways);

	// Set up "look" bindings.
	PlayerInputComponent->BindAxis("Turn", this, &AFPSCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AFPSCharacter::AddControllerPitchInput);

	// Set up "Jump" action.
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::StopJump);

	//Set up "Shoot" action
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AFPSCharacter::Shoot);

	//Set up "Pickup" action
	PlayerInputComponent->BindAction("Pickup", IE_Pressed, this, &AFPSCharacter::Pickup);

	//Set up "Suck" action
	PlayerInputComponent->BindAction("Suck", IE_Pressed, this, &AFPSCharacter::Suck);
	PlayerInputComponent->BindAction("Suck", IE_Released, this, &AFPSCharacter::Suck);

}

void AFPSCharacter::MoveForward(float Value)
{
	//Find out which way is "forward" and record that the player wants to move that way.
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void AFPSCharacter::MoveSideways(float Value)
{
	//Find out which way is "right" and record that the player wants to move that way.
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void AFPSCharacter::StartJump()
{
	bPressedJump = true;
}

void AFPSCharacter::StopJump()
{
	bPressedJump = false;
}

void AFPSCharacter::Shoot()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Shoot"));

	//Get Camera Rotation, slightly angle it up
	FRotator CameraRotation;
	CameraRotation = GetController()->GetControlRotation();
	CameraRotation.Pitch += 10.0f;
	
	//Get Current Item in inventory and grab the actor
	UInventorySystem* Inv = Cast<UInventorySystem>(Inventory);
	if (!Inv) return;
	bool bSuccess = false;
	FItem CurrentItem = Inv->GetCurrentItem(bSuccess);
	if (!bSuccess) return;
	TSubclassOf<AActor> MyActorClass = CurrentItem.ItemActor;
	if (!MyActorClass || !ShootPoint) return;
	//Set Actor params and instantiate it
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();
	AActor* Actor = GetWorld()->SpawnActor<AActor>(MyActorClass, ShootPoint->GetComponentLocation(), ShootPoint->GetComponentRotation(), SpawnParams);
	if (!Actor) return;
	//Remove item from inventory, if it doesnt exists destroy actor and return
	if (!Inv->RemoveItem(CurrentItem.ID))
	{
		Actor->Destroy();
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Spawned"));
	//Launch actor
	FVector LaunchDirection = CameraRotation.Vector();
	UPrimitiveComponent* Prim = Actor->FindComponentByClass<UPrimitiveComponent>();
	if (!Prim) return;

	int32 LaunchPower = CurrentItem.LaunchPower;
	Prim->SetPhysicsLinearVelocity(LaunchDirection * LaunchPower);
	//If Actor has skeletal mesh launch it too
	USkeletalMeshComponent* SkeletalMesh = Actor->FindComponentByClass<USkeletalMeshComponent>();
	if (SkeletalMesh)
	{
		SkeletalMesh->SetPhysicsLinearVelocity(LaunchDirection * LaunchPower);
	}
}


void AFPSCharacter::Suck()
{
	TArray<AActor*> Result;
	GetOverlappingActors(Result, AEnemy::StaticClass());

	//Iterate through the list of actors and suck in those that are able to be picked up
	for (auto actor : Result)
	{
		AEnemy* Enemy = Cast<AEnemy>(actor);
		Enemy->SuckIn();
	}
	
}

void AFPSCharacter::Pickup()
{
	if (CurrentPickup)
	{
		bHoldingItem = !bHoldingItem;
		CurrentPickup->PickupActor();

		if (!bHoldingItem)
		{
			CurrentPickup = nullptr;
		}
	}
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "SlimeTriggerBox.h"
#include "DrawDebugHelpers.h"

ASlimeTriggerBox::ASlimeTriggerBox()
{
    //Register Events
    OnActorBeginOverlap.AddDynamic(this, &ASlimeTriggerBox::OnOverlapBegin);
    OnActorEndOverlap.AddDynamic(this, &ASlimeTriggerBox::OnOverlapEnd);
}

void ASlimeTriggerBox::BeginPlay()
{
    Super::BeginPlay();

    DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Purple, true, -1, 0, 5);

}

void ASlimeTriggerBox::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
    // check if Actors do not equal nullptr and that 
    if (OtherActor && (OtherActor != this)) {
        if (OtherActor->IsA(AEnemy::StaticClass()))
        {
            if (Cast<AEnemy>(OtherActor)->ID == "01") //if slime
            {
                GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Detect"));
                AAdavcned_GameEngineGameModeBase* GameMode = Cast<AAdavcned_GameEngineGameModeBase>(GetWorld()->GetAuthGameMode());
                GameMode->SlimeCounter++;
                GameMode->CheckSlimesAmount();
                OtherActor->Destroy();
            }
            
        }
    }
}

void ASlimeTriggerBox::OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor)
{
   
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Maps/NP_AfterCCTV.h"
#include "Components/BoxComponent.h"
#include "Components/StageControll/NPCH0Component.h"
#include "Interface/StageControlInterface.h"
#include "GameFramework/GameModeBase.h"
#include "NPFunctionLibrary.h"

#include "DebugHelper.h"

ANP_AfterCCTV::ANP_AfterCCTV()
{
	USceneComponent* DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SetRootComponent(DefaultSceneRoot);

	ItemCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ItemCollisionBox"));
	ItemCollisionBox->SetupAttachment(DefaultSceneRoot);
	ItemCollisionBox->SetBoxExtent(FVector(20.f));
	// No Physics Option
	ItemCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ItemCollisionBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	ItemCollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

}

void ANP_AfterCCTV::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld() && GetWorld()->GetAuthGameMode())
	{
		if (IStageControlInterface* StageControlInterface = Cast<IStageControlInterface>(GetWorld()->GetAuthGameMode()))
		{
			CCTVComponent = StageControlInterface->GetCh0Component();

			if (CCTVComponent)
			{
				CCTVComponent->OnRun.AddDynamic(this, &ANP_AfterCCTV::StartEvent);
			}
		}
	}

	if (ItemCollisionBox)
	{
		ItemCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ANP_AfterCCTV::OnOverlapDarkWall);
	}

}

void ANP_AfterCCTV::OnOverlapDarkWall(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APawn* PlayerPawn = Cast<APawn>(OtherActor);
	if (PlayerPawn && PlayerPawn->IsPlayerControlled())
	{
		UNPFunctionLibrary::call_died(this);
	}
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "Gamemodes/NPBaseGamemode.h"
#include "Interface/PawnUIInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Components/UI/NarrationalUIComponent.h"
#include "NPGameInstance.h"

void ANPBaseGamemode::BeginPlay()
{
	Super::BeginPlay();

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(PlayerPawn))
	{
		if (UNarrationalUIComponent* NarrationUIComponent = PawnUIInterface->GetNarrationUIComponent())
		{
			BP_OnOwningNarrtionUIComponentInitialized(NarrationUIComponent);
		}
	}
}

void ANPBaseGamemode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ANPBaseGamemode::EndChapter(FGameplayTag NextChapter)
{
	UNPGameInstance* InstanceProgress = GetGameInstance<UNPGameInstance>();
	if (!InstanceProgress) return;

	InstanceProgress->SetCurrentChapter(NextChapter);
	TSoftObjectPtr<UWorld> NextLevelPtr = InstanceProgress->GetLevelForChapter(NextChapter);

	if (!NextLevelPtr.IsNull())
	{
		UGameplayStatics::OpenLevelBySoftObjectPtr(this, NextLevelPtr);
	}
}

void ANPBaseGamemode::SetCurrentGameState(ENPGameState NewState)
{
	CurrentGameState = NewState;

	OnGameStateChanged.Broadcast(CurrentGameState);
}

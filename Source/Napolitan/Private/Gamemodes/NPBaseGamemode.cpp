// Fill out your copyright notice in the Description page of Project Settings.


#include "Gamemodes/NPBaseGamemode.h"
#include "Interface/PawnUIInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Components/UI/NarrationalUIComponent.h"
#include "NPGameInstance.h"
#include "NPFunctionLibrary.h"
#include "EngineUtils.h"
#include "GameFramework/PlayerStart.h"

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

AActor* ANPBaseGamemode::ChoosePlayerStart_Implementation(AController* Player)
{
	FString TargetTag = UNPFunctionLibrary::GetNPGameInstance(GetWorld())->GetCurrentChapter().ToString();

	for (TActorIterator<APlayerStart> It(GetWorld()); It; ++It)
	{
		APlayerStart* Start = *It;
		if (Start && Start->PlayerStartTag.ToString() == TargetTag)
		{
			return Start;
		}
	}

	return Super::ChoosePlayerStart_Implementation(Player);
}

void ANPBaseGamemode::TeleportToPlayerStart(const UObject* WorldContextObject, FName TargetTag)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (!World) return;

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(World, 0);
	if (!PlayerPawn) return;

	for (TActorIterator<APlayerStart> It(World); It; ++It)
	{
		APlayerStart* Start = *It;

		if (Start && Start->PlayerStartTag == TargetTag)
		{
			PlayerPawn->SetActorLocationAndRotation(
				Start->GetActorLocation(),
				Start->GetActorRotation(),
				false, nullptr, ETeleportType::TeleportPhysics
			);
			return;
		}
	}
}

void ANPBaseGamemode::SaveGameInstance()
{
	UNPFunctionLibrary::SaveInventoryToInstance(this);
}

FGameplayTag ANPBaseGamemode::ChapterStartManager()
{
	FGameplayTag CurrChap = UNPFunctionLibrary::GetNPGameInstance(this)->GetCurrentChapter();

	TeleportToPlayerStart(this, FName(*CurrChap.ToString()));

	return CurrChap;
}

void ANPBaseGamemode::EndChapter(FGameplayTag NextChapter)
{
	UNPGameInstance* InstanceProgress = GetGameInstance<UNPGameInstance>();
	if (!InstanceProgress) return;

	InstanceProgress->SetCurrentChapter(NextChapter);
	TSoftObjectPtr<UWorld> NextLevelPtr = InstanceProgress->GetLevelForChapter(NextChapter);

	SaveGameInstance();

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

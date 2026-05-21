// Fill out your copyright notice in the Description page of Project Settings.


#include "NPFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "NPGameplayTag.h"
#include "NPGameInstance.h"
#include "SaveGame/NPSaveGame.h"
#include "SaveGame/NPMetaSaveGame.h"
#include "Character/NPPlayerCharacter.h"
#include "Gamemodes/NPBaseGamemode.h"

#include "DebugHelper.h"

UNPGameInstance* UNPFunctionLibrary::GetNPGameInstance(const UObject* WorldContextObject)
{
	if (GEngine)
	{
		if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
		{
			return World->GetGameInstance<UNPGameInstance>();
		}
	}

	return nullptr;
}

void UNPFunctionLibrary::SaveInventoryToInstance(const AActor* ContextActor)
{
	if (!ContextActor) return;

	ANPPlayerCharacter* Player = Cast<ANPPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(ContextActor, 0));
	UNPGameInstance* GI = Cast<UNPGameInstance>(UGameplayStatics::GetGameInstance(ContextActor));

	if (Player && GI)
	{
		GI->InventoryInstance = Player->GetInventoryComponentDefualt()->SaveInventory();
		UE_LOG(LogTemp, Log, TEXT("Inventory successfully moved to GameInstance!"));
	}
}

void UNPFunctionLibrary::SaveCurrentGameInstance(UNPGameInstance* SaveData, const FGameplayTag& SlotName)
{
	if (SaveData->CurrentChapter.IsValid() == false)
	{
		Debug::Print(TEXT("Current Chapter is Invalid, Game Instance Not Saved"));
		return;
	}

	USaveGame* SaveGameObject = UGameplayStatics::CreateSaveGameObject(UNPSaveGame::StaticClass());

	if (UNPSaveGame* NPSaveData = Cast<UNPSaveGame>(SaveGameObject))
	{
		// Implement SaveData Individually
		NPSaveData->EventOccurred = SaveData->EventOccurred;
		NPSaveData->CurrentChapter = SaveData->CurrentChapter;
		NPSaveData->InventoryInstance = SaveData->InventoryInstance;

		const bool bWasSaved = UGameplayStatics::SaveGameToSlot(NPSaveData, SlotName.ToString(), 0);

		Debug::Print(bWasSaved ? TEXT("Game Instance Saved") : TEXT("Game Instance Not Saved"));
	}
}

bool UNPFunctionLibrary::TryLoadGameInstance(UNPGameInstance* LoadData, const FGameplayTag& SlotName)
{
	if (UGameplayStatics::DoesSaveGameExist(SlotName.ToString(), 0))
	{
		if (USaveGame* LoadGameObject = UGameplayStatics::LoadGameFromSlot(SlotName.ToString(), 0))
		{
			if (UNPSaveGame* NPLoadData = Cast<UNPSaveGame>(LoadGameObject))
			{
				LoadData->EventOccurred = NPLoadData->EventOccurred;
				LoadData->CurrentChapter = NPLoadData->CurrentChapter;
				LoadData->InventoryInstance = NPLoadData->InventoryInstance;

				if (GetLastSaveData() != SlotName)
				{
					SetLastSaveData(SlotName);
				}

				Debug::Print(TEXT("Game Instance Loaded"));
				return true;
			}
		}
	}

	return false;
}

void UNPFunctionLibrary::DeleteSaveData(const FGameplayTag& SlotName)
{
	if (UGameplayStatics::DoesSaveGameExist(SlotName.ToString(), 0))
	{
		UGameplayStatics::DeleteGameInSlot(SlotName.ToString(), 0);

		if (GetLastSaveData() == SlotName)
		{
			SetLastSaveData(FGameplayTag());
		}

		Debug::Print(TEXT("Save Data Deleted"));
	}
}

FGameplayTag UNPFunctionLibrary::GetLastSaveData()
{
	if (UGameplayStatics::DoesSaveGameExist(NPGamplayTags::GameData_SaveGame_MetaData.GetTag().ToString(), 0))
	{
		if (USaveGame* LoadGameObject = UGameplayStatics::LoadGameFromSlot(NPGamplayTags::GameData_SaveGame_MetaData.GetTag().ToString(), 0))
		{
			if (UNPMetaSaveGame* NPLoadData = Cast<UNPMetaSaveGame>(LoadGameObject))
			{
				return NPLoadData->LastPlayedData;
			}
		}
	}

	return FGameplayTag();
}

void UNPFunctionLibrary::SetLastSaveData(const FGameplayTag& SlotName)
{
	const FString MetaSlotName = NPGamplayTags::GameData_SaveGame_MetaData.GetTag().ToString();
	UNPMetaSaveGame* MetaSaveObj = nullptr;

	if (UGameplayStatics::DoesSaveGameExist(MetaSlotName, 0))
	{
		MetaSaveObj = Cast<UNPMetaSaveGame>(UGameplayStatics::LoadGameFromSlot(MetaSlotName, 0));
	}

	if (!MetaSaveObj)
	{
		MetaSaveObj = Cast<UNPMetaSaveGame>(UGameplayStatics::CreateSaveGameObject(UNPMetaSaveGame::StaticClass()));
	}

	if (MetaSaveObj)
	{
		MetaSaveObj->LastPlayedData = SlotName;
		UGameplayStatics::SaveGameToSlot(MetaSaveObj, MetaSlotName, 0);
	}
}

FGameplayTag UNPFunctionLibrary::FindFirstEmptySlotIndex(int32 MaxSlots)
{
	for (int32 i = 1; i <= MaxSlots; ++i)
	{
		FString SlotName = FString::Printf(TEXT("GameData.SaveGame.Slot.%d"), i);

		if (!UGameplayStatics::DoesSaveGameExist(SlotName, 0))
		{
			return FGameplayTag::RequestGameplayTag(FName(*SlotName), false);
		}
	}

	return FGameplayTag();
}

FGameplayTag UNPFunctionLibrary::GetSaveSlotSummary(FGameplayTag SlotTag)
{
	if (UGameplayStatics::DoesSaveGameExist(SlotTag.ToString(), 0))
	{
		if (UNPSaveGame* LoadedData = Cast<UNPSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotTag.ToString(), 0)))
		{
			return LoadedData->CurrentChapter;
		}
	}
	return FGameplayTag();
}

void UNPFunctionLibrary::call_died(const UObject* WorldContextObject)
{
	GetNPGameInstance(WorldContextObject)->SetCurrentGameState(ENPGameState::GameOver);
}
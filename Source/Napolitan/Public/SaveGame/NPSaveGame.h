// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "NPGameplayTag.h"
#include "Components/Items/ItemInventoryComponentBase.h"
#include "NPSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class NAPOLITAN_API UNPSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly)
	TArray<FGameplayTag> EventOccurred;

	UPROPERTY(BlueprintReadOnly)
	FGameplayTag CurrentChapter;

	UPROPERTY(BlueprintReadOnly)
	TMap<EItemCategory, FInventoryArray> InventoryInstance;
};

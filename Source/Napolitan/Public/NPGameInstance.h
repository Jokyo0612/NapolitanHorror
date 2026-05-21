// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "NPGameplayTag.h"
#include "Components/Items/ItemInventoryComponentBase.h"
#include "NPGameInstance.generated.h"

UENUM(BlueprintType)
enum class ENPGameState : uint8
{
	WaitingToStart UMETA(DisplayName = "Waiting To Start"),
	InProgress UMETA(DisplayName = "In Progress"),
	Paused UMETA(DisplayName = "Paused"),
	GameOver UMETA(DisplayName = "Game Over")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameStateChanged, ENPGameState, CurrentState);

USTRUCT(BlueprintType)
struct FNPChapterData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, meta=(Categories = "Chapter"))
	FGameplayTag ChapterTag;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> Level;

	bool IsValid() const
	{
		return ChapterTag.IsValid() && !Level.IsNull();
	}
};
/**
 */
UCLASS()
class NAPOLITAN_API UNPGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Data")
	TArray<FNPChapterData> ChapterData;

public:
	UPROPERTY(VisibleAnywhere, Category = "Game Instance")
	TArray<FGameplayTag> EventOccurred;

	UPROPERTY(VisibleAnywhere, Category = "Game Instance")
	FGameplayTag CurrentChapter;

	UPROPERTY(VisibleAnywhere, Category = "Game Instance")
	TMap<EItemCategory, FInventoryArray> InventoryInstance;

public:
	UFUNCTION(BlueprintPure, Category = "Game Data", meta = (GameplayTagFilter = "Chapter"))
	TSoftObjectPtr<UWorld> GetLevelForChapter(FGameplayTag ChapterTag) const;

	UFUNCTION(BlueprintCallable, Category = "Game Instance")
	void SetCurrentChapter(FGameplayTag ChapterTag);

	UFUNCTION(BlueprintPure, Category = "Game Instance")
	FGameplayTag GetCurrentChapter() const;
	
	UFUNCTION(BlueprintCallable, Category = "Game Instance")
	void AddEvent(FGameplayTag EventTag);

	UFUNCTION(BlueprintPure, Category = "Game Instance")
	bool HasEventOccurred(FGameplayTag EventTag) const;

#pragma region Game State

public:
	void SetCurrentGameState(ENPGameState NewState);

private:
	UPROPERTY()
	ENPGameState CurrentGameState;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnGameStateChanged OnGameStateChanged;

#pragma endregion
};

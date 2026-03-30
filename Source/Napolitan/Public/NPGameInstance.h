// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "NPGameplayTag.h"
#include "NPGameInstance.generated.h"

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

private:
	UPROPERTY(VisibleAnywhere, Category = "Game Instance")
	TArray<FGameplayTag> EventOccurred;

	UPROPERTY(VisibleAnywhere, Category = "Game Instance")
	FGameplayTag CurrentChapter;

	virtual void Init() override;

public:
	UFUNCTION(BlueprintPure, Category = "Game Data", meta = (GameplayTagFilter = "Chapter"))
	TSoftObjectPtr<UWorld> GetLevelForChapter(FGameplayTag ChapterTag) const;

	UFUNCTION(BlueprintCallable, Category = "Game Instance")
	void SetCurrentChapter(const FGameplayTag& ChapterTag);

	UFUNCTION(BlueprintPure, Category = "Game Instance")
	FGameplayTag GetCurrentChapter() const;
	
	UFUNCTION(BlueprintCallable, Category = "Game Instance")
	void AddEvent(const FGameplayTag& EventTag);

	UFUNCTION(BlueprintPure, Category = "Game Instance")
	bool HasEventOccurred(const FGameplayTag& EventTag) const;
};

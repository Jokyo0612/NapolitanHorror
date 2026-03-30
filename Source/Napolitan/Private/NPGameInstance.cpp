// Fill out your copyright notice in the Description page of Project Settings.


#include "NPGameInstance.h"

void UNPGameInstance::Init()
{
	Super::Init();

	// Implement to load last data from save game
}

TSoftObjectPtr<UWorld> UNPGameInstance::GetLevelForChapter(FGameplayTag ChapterTag) const
{
	for (const FNPChapterData& Chapter : ChapterData)
	{
		if (!Chapter.IsValid())	continue;
		
		if (Chapter.ChapterTag == ChapterTag)
		{
			return Chapter.Level;
		}
	}

	return TSoftObjectPtr<UWorld>();
}

void UNPGameInstance::SetCurrentChapter(const FGameplayTag& ChapterTag)
{
	if (CurrentChapter != ChapterTag)
	{
		CurrentChapter = ChapterTag;
	}
}

FGameplayTag UNPGameInstance::GetCurrentChapter() const
{
	return CurrentChapter;
}

void UNPGameInstance::AddEvent(const FGameplayTag& EventTag)
{
	if (EventTag.IsValid() && !EventOccurred.Contains(EventTag))
	{
		EventOccurred.Add(EventTag);
	}
}

bool UNPGameInstance::HasEventOccurred(const FGameplayTag& EventTag) const
{
	if(EventTag.IsValid())
	{
		return EventOccurred.Contains(EventTag);
	}

	return false;
}

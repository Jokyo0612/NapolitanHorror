// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/NPGeneralWidgetSettings.h"
#include "NPSaveSlotWidgetInv.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSaveSlotClicked, const FString&, ATag);

/**
 * 
 */
UCLASS()
class NAPOLITAN_API UNPSaveSlotWidgetInv : public UNPGeneralWidgetSettings
{
	GENERATED_BODY()
	
public:
	void UpdateSaveSlot(FString ChapterName, FString TagName);

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Save Game")
	FOnSaveSlotClicked OnSaveSlotClicked;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Save Game")
	FString AChapterName;

	UPROPERTY(BlueprintReadOnly, Category = "Save Game")
	FString ATagName;

	UFUNCTION(BlueprintImplementableEvent, Category = "Save Game")
	void BP_UpdateSaveSlots();
};

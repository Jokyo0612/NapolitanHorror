// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/NPGeneralWidgetSettings.h"
#include "NPSaveSlotWidgetBase.generated.h"

class UPanelWidget;
class UNPSaveSlotWidgetInv;

/**
 * 
 */
UCLASS()
class NAPOLITAN_API UNPSaveSlotWidgetBase : public UNPGeneralWidgetSettings
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UPanelWidget> SaveSlotContainer;

	UFUNCTION(BlueprintCallable, Category = "Save Game")
	void RefreshSaveSlots();

	UFUNCTION(BlueprintCallable, Category = "Save Game")
	FGameplayTag StringToGameplayTag(const FString& TagString) const;

	TArray<UNPSaveSlotWidgetInv*> SaveSlotWidgets;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Handle Clicked Button Event"))
	void HandleSaveSlotClicked(const FString& SlotName);
};

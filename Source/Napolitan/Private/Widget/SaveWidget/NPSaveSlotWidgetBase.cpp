// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SaveWidget/NPSaveSlotWidgetBase.h"
#include "NPGameplayTag.h"
#include "Components/PanelWidget.h"
#include "NPFunctionLibrary.h"
#include "Widget/SaveWidget/NPSaveSlotWidgetInv.h"

void UNPSaveSlotWidgetBase::RefreshSaveSlots()
{
	SaveSlotWidgets.Empty();
	int i = 1;

	for (UWidget* Child : SaveSlotContainer->GetAllChildren())
	{
		if (UNPSaveSlotWidgetInv* SaveSlot = Cast<UNPSaveSlotWidgetInv>(Child))
		{
			FString TagName = FString::Printf(TEXT("GameData.SaveGame.Slot.%d"), i++);
			FGameplayTag ChapterName = UNPFunctionLibrary::GetSaveSlotSummary(StringToGameplayTag(TagName));

			if (!ChapterName.IsValid())
			{
				SaveSlot->SetVisibility(ESlateVisibility::Collapsed);
			}
			else 
			{
				FString ChapterNameStr = ChapterName.ToString();
				SaveSlotWidgets.Add(SaveSlot);
				SaveSlot->UpdateSaveSlot(ChapterNameStr, TagName);
				SaveSlot->OnSaveSlotClicked.AddDynamic(this, &UNPSaveSlotWidgetBase::HandleSaveSlotClicked);
			}
		}
	}
}

FGameplayTag UNPSaveSlotWidgetBase::StringToGameplayTag(const FString& TagString) const
{
	return TagString.IsEmpty() ? FGameplayTag() : FGameplayTag::RequestGameplayTag(FName(*TagString));
}

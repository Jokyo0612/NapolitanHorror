// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/SaveWidget/NPSaveSlotWidgetInv.h"

void UNPSaveSlotWidgetInv::UpdateSaveSlot(FString ChapterName, FString TagName)
{
	this->AChapterName = ChapterName;
	this->ATagName = TagName;
	BP_UpdateSaveSlots();
}

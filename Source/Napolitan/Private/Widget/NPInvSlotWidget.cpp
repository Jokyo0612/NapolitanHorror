// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/NPInvSlotWidget.h"
#include "DataAssets/S_ItemInfo.h"
#include "Components/Items/ItemInventoryComponentBase.h"


void UNPInvSlotWidget::UpdateSlot(FName NewItemID, FS_Item* ItemData)
{
    CurrentItemID = NewItemID;

    if (CurrentItemID.IsNone())
    {
        SetVisibility(ESlateVisibility::Collapsed);
        return;
    }

    FS_Item* Data = ItemData;
    if (Data)
    {
        CachedItemData = *Data;

        BP_UpdateVisuals();
    }
}
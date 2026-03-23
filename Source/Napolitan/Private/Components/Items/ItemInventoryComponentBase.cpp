// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Items/ItemInventoryComponentBase.h"
#include "DataAssets/S_ItemInfo.h"

#include "DebugHelper.h"

bool UItemInventoryComponentBase::AddItem(FName NewItem)
{
    if (!ItemDataTable)
    {
        Debug::Print(TEXT("Data Table is not allocated"));
        return false;
    }

    FS_Item* ItemData = ItemDataTable->FindRow<FS_Item>(NewItem, TEXT(""));

    if (ItemData && !Items.Contains(NewItem))
    {
        Items.Add(NewItem);
        OnInventoryUpdated.Broadcast(NewItem);

        Debug::Print((TEXT("Items acquired : %s"), *ItemData->ItemName.ToString()));

        Debug::Print(TEXT("Inventory now on"));
        for (auto item : Items)
        {
            Debug::Print((TEXT("&s"), item.ToString()));
        }

        return true;
    }

    return false;
}

void UItemInventoryComponentBase::UseItem(FName ItemToUse)
{
	// Player Event State Check Needed

	if (Items.Contains(ItemToUse))
	{
		Items.Remove(ItemToUse);
	}
}

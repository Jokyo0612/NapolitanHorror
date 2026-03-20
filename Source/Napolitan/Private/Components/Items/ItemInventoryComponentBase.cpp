// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Items/ItemInventoryComponentBase.h"
#include "DataAssets/DataAsset_ItemInfo.h"

#include "DebugHelper.h"

void UItemInventoryComponentBase::AddItem(UDataAsset_ItemInfo* NewItem)
{
	if (!Items.Contains(NewItem))
	{
		Items.Add(NewItem);
		OnInventoryUpdated.Broadcast(NewItem);

		Debug::Print(TEXT("Now on Inventory"));
		for (auto item : Items)
		{
			if (IsValid(item))
			{
				Debug::Print((TEXT("%s"), *item->ItemName.ToString()));
			}
		}
	}	
}

void UItemInventoryComponentBase::UseItem(UDataAsset_ItemInfo* ItemToUse)
{
	// Player Event State Check Needed

	if (Items.Contains(ItemToUse))
	{
		Items.Remove(ItemToUse);

		Debug::Print(TEXT("Now on Inventory"));
		for (auto item : Items)
		{
			if (IsValid(item))
			{
				Debug::Print((TEXT("%s"), *item->ItemName.ToString()));
			}
		}
	}
}

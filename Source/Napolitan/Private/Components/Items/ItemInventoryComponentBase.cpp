// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Items/ItemInventoryComponentBase.h"
#include "DataAssets/S_ItemInfo.h"
#include "NPGameInstance.h"
#include "NPFunctionLibrary.h"

void UItemInventoryComponentBase::BeginPlay()
{
    Super::BeginPlay();

    if (UNPGameInstance* GI = UNPFunctionLibrary::GetNPGameInstance(this))
    {
        CategorizedItems = GI->InventoryInstance;
    }

    CategorizedItems.FindOrAdd(EItemCategory::Usable);
    CategorizedItems.FindOrAdd(EItemCategory::Quest);
    CategorizedItems.FindOrAdd(EItemCategory::ReadOnly);

}

bool UItemInventoryComponentBase::AddItem(FName NewItem)
{
    if (!ItemDataTable)
    {
        UE_LOG(LogTemp, Display, TEXT("ItemTable Not Allocated"));
        return false;
    }

    FS_Item* ItemData = ItemDataTable->FindRow<FS_Item>(NewItem, TEXT(""));

    TArray<FName>& InventorySection = CategorizedItems[ItemData->ItemType].Items;

    if (ItemData && !InventorySection.Contains(NewItem))
    {
        InventorySection.Add(NewItem);

        // 실시간 업데이트 필요시 델리게이트 정의
        // OnInventoryUpdated.Broadcast(NewItem);

        return true;
    }

    return false;
}

void UItemInventoryComponentBase::UseItem(FName ItemToUse)
{
	// Player Event State Check Needed

    FS_Item* ItemData = ItemDataTable->FindRow<FS_Item>(ItemToUse, TEXT(""));

    TArray<FName>& InventorySection = CategorizedItems[ItemData->ItemType].Items;

	if (InventorySection.Contains(ItemToUse))
	{
        InventorySection.Remove(ItemToUse);
	}
}

const TArray<FName>& UItemInventoryComponentBase::GetItems(EItemCategory Category) const
{
    return CategorizedItems[Category].Items;
}

FS_Item* UItemInventoryComponentBase::GetItemData(FName ItemID) const
{
    if (!ItemDataTable) return nullptr;

    return ItemDataTable->FindRow<FS_Item>(ItemID, TEXT("GetItemData"));
}

FS_Item UItemInventoryComponentBase::BP_GetItemData(FName ItemID, bool& bSuccess) const
{
    FS_Item* FoundData = GetItemData(ItemID);

    bSuccess = (FoundData != nullptr);

    return bSuccess ? *FoundData : FS_Item();
}

TMap<EItemCategory, FInventoryArray> UItemInventoryComponentBase::SaveInventory() const
{
    return CategorizedItems;
}


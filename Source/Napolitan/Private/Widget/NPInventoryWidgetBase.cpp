// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/NPInventoryWidgetBase.h"
#include "Interface/InventoryInterface.h"
#include "Components/Items/ItemInventoryComponentBase.h"
#include "DataAssets/S_ItemInfo.h"
#include "Widget/NPInvSlotWidget.h"
#include "Blueprint/WidgetTree.h"

void UNPInventoryWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (IInventoryInterface* PawnInventoryInterface = Cast<IInventoryInterface>(GetOwningPlayerPawn()))
	{
		if (PlayerInventoryComponent = PawnInventoryInterface->GetInventoryComponentDefualt())
		{
			BP_OnOwningHeroInventoryComponentInitialized(PlayerInventoryComponent);
		}
	}

    if (WidgetTree)
    {
        WidgetTree->ForEachWidget([this](UWidget* Widget)
        {
            if (UNPInvSlotWidget* NewSlot = Cast<UNPInvSlotWidget>(Widget))
            {
                InvSlots.Add(NewSlot);
                NewSlot->OnSlotClicked.AddDynamic(this, &UNPInventoryWidgetBase::HandleSlotClick);
            }
        });
    }

}

void UNPInventoryWidgetBase::RefreshInventory()
{
    if (!PlayerInventoryComponent) return;

    const TArray<FName>& Items = PlayerInventoryComponent->GetItems(CurrentViewCategory);

    for (int32 i = 0; i < InvSlots.Num(); ++i)
    {
        if (Items.IsValidIndex(i))
        {
            const FName& ItemID = Items[i];
            InvSlots[i]->UpdateSlot(ItemID, PlayerInventoryComponent->GetItemData(ItemID));
            InvSlots[i]->SetVisibility(ESlateVisibility::Visible);
        }
        else
        {
            InvSlots[i]->SetVisibility(ESlateVisibility::Hidden);
        }
    }
}

void UNPInventoryWidgetBase::OnTabButtonClicked(EItemCategory NewCategory)
{
    CurrentViewCategory = NewCategory;
    RefreshInventory();
}

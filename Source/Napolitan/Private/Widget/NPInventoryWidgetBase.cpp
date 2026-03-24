// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/NPInventoryWidgetBase.h"
#include "Interface/InventoryInterface.h"
#include "Components/Items/ItemInventoryComponentBase.h"
#include "DataAssets/S_ItemInfo.h"
#include "Components/PanelWidget.h"
#include "Widget/NPInvSlotWidget.h"

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

    InventorySections.Add(EItemCategory::Usable, { UsableSlotContainer });
    InventorySections.Add(EItemCategory::Quest, { QuestSlotContainer });
    InventorySections.Add(EItemCategory::ReadOnly, { ReadOnlySlotContainer });

    for (auto& Pair : InventorySections)
    {
        if (Pair.Value.Container)
        {
            for (UWidget* Child : Pair.Value.Container->GetAllChildren())
            {
                if (UNPInvSlotWidget* NewSlot = Cast<UNPInvSlotWidget>(Child))
                {
                    Pair.Value.InvSlots.Add(NewSlot);

                    NewSlot->OnSlotClicked.AddDynamic(this, &UNPInventoryWidgetBase::HandleSlotClick);
                }
            }
        }
    }
}

void UNPInventoryWidgetBase::RefreshInventory()
{
    if (!PlayerInventoryComponent) return;

    const TArray<EItemCategory> MainCategory = {
        EItemCategory::Usable,
        EItemCategory::Quest,
        EItemCategory::ReadOnly
    };

    for (const EItemCategory Category : MainCategory)
    {
        const TArray<FName>& Items = PlayerInventoryComponent->GetItems(Category);

        if (!InventorySections.Contains(Category))
        {
            UE_LOG(LogTemp, Warning, TEXT("Category %d not found in InventorySections!"), (int32)Category);
            continue;
        }

        auto& Section = InventorySections[Category];

        int32 SlotIdx = 0;

        for (const FName& ItemID : Items)
        {
            if (Section.InvSlots.IsValidIndex(SlotIdx))
            {
                Section.InvSlots[SlotIdx]->UpdateSlot(ItemID, PlayerInventoryComponent->GetItemData(ItemID));
                Section.InvSlots[SlotIdx]->SetVisibility(ESlateVisibility::Visible);
                SlotIdx++;
            }
        }

        for (int32 i = SlotIdx; i < Section.InvSlots.Num(); ++i)
        {
            Section.InvSlots[i]->SetVisibility(ESlateVisibility::Collapsed);
        }
    }
}


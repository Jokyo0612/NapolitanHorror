// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/NPItem_Getable.h"
#include "Interface/InventoryInterface.h"
#include "Components/Items/ItemInventoryComponentBase.h"
#include "Components/InteractUIComponent.h"

void ANPItem_Getable::Interact_Implementation(AActor* Interactor)
{
	if (!Interactor || ItemHandle.IsNull() || !InteractionHandler->bInteractable) return;

	if (IInventoryInterface* PawnInventoryInterface = Cast<IInventoryInterface>(Interactor))
	{
		if (UItemInventoryComponentBase* PlayerInventoryComponent = PawnInventoryInterface->GetInventoryComponentDefualt())
		{
			if (PlayerInventoryComponent->AddItem(ItemHandle.RowName))
			{
				// Need to Implementating Acquiring Effect
				// PlayAcquireEffects();

				BP_OnGetableItemInteract(Interactor);

				Destroy();				
			}
		}
	}
}

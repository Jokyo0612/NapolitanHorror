// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/NPItem_Getable.h"
#include "Interface/InventoryInterface.h"
#include "Components/Items/ItemInventoryComponentBase.h"

#include "DebugHelper.h"

void ANPItem_Getable::Interact_Implementation(AActor* Interactor)
{
	Debug::Print((TEXT("Interactor : %s"), Interactor->GetActorNameOrLabel()));

	if (!Interactor || ItemHandle.IsNull()) return;

	if (IInventoryInterface* PawnInventoryInterface = Cast<IInventoryInterface>(Interactor))
	{
		if (UItemInventoryComponentBase* PlayerInventoryComponent = PawnInventoryInterface->GetInventoryComponentDefualt())
		{
			if (PlayerInventoryComponent->AddItem(ItemHandle.RowName))
			{
				// Need to Implementating Acquiring Effect
				// PlayAcquireEffects();

				Destroy();
			}
		}
	}

}

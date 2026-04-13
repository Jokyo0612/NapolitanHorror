// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NPNPCCharacter.h"
#include "Interface/PawnUIInterface.h"
#include "Interface/InventoryInterface.h"
#include "Components/UI/NarrationalUIComponent.h"

void ANPNPCCharacter::Interact_Implementation(AActor* Interactor)
{
    if (!Interactor || !bInteractable) return;

    if (bInteractable)
    {
		bInteractable = false;

        IPawnUIInterface* PawnUI = Cast<IPawnUIInterface>(Interactor);
        IInventoryInterface* PawnInv = Cast<IInventoryInterface>(Interactor);

        if (PawnUI && PawnInv)
        {
            UNarrationalUIComponent* NarrationComp = PawnUI->GetNarrationUIComponent();
            UItemInventoryComponentBase* Inventory = PawnInv->GetInventoryComponentDefualt();

            if (NarrationComp && Inventory)
            {
                BP_OnNPCInteractionCalled(NarrationComp, Inventory);
            }
        }
    }

}
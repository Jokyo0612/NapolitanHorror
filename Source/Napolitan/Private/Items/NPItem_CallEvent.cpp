// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/NPItem_CallEvent.h"
#include "Interface/PawnUIInterface.h"
#include "Components/InteractUIComponent.h"

void ANPItem_CallEvent::Interact_Implementation(AActor* Interactor)
{
	if (!Interactor || !InteractionHandler->bInteractable) return;

	if (IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(Interactor))
	{
		if (UNarrationalUIComponent* NarrationUIComponent = PawnUIInterface->GetNarrationUIComponent())
		{
			BP_OnCallItemInteract(NarrationUIComponent);
		}
	}
}

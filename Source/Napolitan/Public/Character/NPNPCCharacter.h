// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/NPBaseCharacter.h"
#include "Interface/InteractInterface.h"
#include "NPNPCCharacter.generated.h"

class UNarrationalUIComponent;
class UItemInventoryComponentBase;

/**
 * 
 */
UCLASS()
class NAPOLITAN_API ANPNPCCharacter : public ANPBaseCharacter, public IInteractInterface
{
	GENERATED_BODY()

protected:
	void Interact_Implementation(AActor* Interactor) override;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On NPC Interact Event"))
	void BP_OnNPCInteractionCalled(UNarrationalUIComponent* OwningPlayerComponent, UItemInventoryComponentBase* Inv);
	
	bool bInteractable = true;
};

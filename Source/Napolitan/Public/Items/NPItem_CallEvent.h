// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/NPItemBase.h"
#include "NPItem_CallEvent.generated.h"

/**
 * 
 */
UCLASS()
class NAPOLITAN_API ANPItem_CallEvent : public ANPItemBase
{
	GENERATED_BODY()

	void Interact_Implementation(AActor* Interactor) override;

protected:
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Owning CallEvent Item"))
	void BP_OnCallItemInteract(UNarrationalUIComponent* OwningPlayerComponent);
	
};

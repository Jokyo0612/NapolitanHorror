// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/NPWidgetBase.h"
#include "NPInventoryWidgetBase.generated.h"

class UItemInventoryComponentBase;
/**
 * 
 */
UCLASS()
class NAPOLITAN_API UNPInventoryWidgetBase : public UNPWidgetBase
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Owning PlayerInventoryComponent Initialized"))
	void BP_OnOwningHeroInventoryComponentInitialized(UItemInventoryComponentBase* OwningPlayerComponent);

};

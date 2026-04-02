// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/NPGeneralWidgetSettings.h"
#include "NPNarrationalWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class NAPOLITAN_API UNPNarrationalWidgetBase : public UNPGeneralWidgetSettings
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;
	
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Owning NarrtionUIComponent Initialized"))
	void BP_OnOwningNarrtionUIComponentInitialized(UNarrationalUIComponent* OwningPlayerComponent);
};

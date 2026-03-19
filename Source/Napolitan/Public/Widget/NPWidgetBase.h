// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NPWidgetBase.generated.h"

class UPlayerUIComponent;

/**
 * 
 */
UCLASS()
class NAPOLITAN_API UNPWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Owning HeroUIComponent Initialized"))
	void BP_OnOwningHeroUIComponentInitialized(UPlayerUIComponent* OwningPlayerComponent);
};

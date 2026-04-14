// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DataAssets/S_ItemInfo.h"
#include "NPInventoryWidgetBase.generated.h"

class UItemInventoryComponentBase;
class UNPInvSlotWidget;
enum class EItemCategory : uint8;

/**
 * 
 */
UCLASS()
class NAPOLITAN_API UNPInventoryWidgetBase : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Owning PlayerInventoryComponent Initialized"))
	void BP_OnOwningHeroInventoryComponentInitialized(UItemInventoryComponentBase* OwningPlayerComponent);

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	TObjectPtr<UItemInventoryComponentBase> PlayerInventoryComponent;

	UPROPERTY()
	TArray<TObjectPtr<UNPInvSlotWidget>> InvSlots;

	UPROPERTY()
	EItemCategory CurrentViewCategory;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Refresh Item Slots"))
	void RefreshInventory();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Handle Tab Button Clicked"))
	void OnTabButtonClicked(EItemCategory Category);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Handle Clicked Button Event"))
	void HandleSlotClick(const FS_Item& ItemData);

};

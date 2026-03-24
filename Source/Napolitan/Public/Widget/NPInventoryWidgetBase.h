// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DataAssets/S_ItemInfo.h"
#include "NPInventoryWidgetBase.generated.h"

class UItemInventoryComponentBase;
class UNPInvSlotWidget;
class UPanelWidget;

USTRUCT(BlueprintType)
struct FInventorySectionData
{
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<UPanelWidget> Container;

	UPROPERTY()
	TArray<TObjectPtr<UNPInvSlotWidget>> InvSlots;
};
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

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UPanelWidget> UsableSlotContainer;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UPanelWidget> QuestSlotContainer;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UPanelWidget> ReadOnlySlotContainer;

	UPROPERTY()
	TMap<EItemCategory, FInventorySectionData> InventorySections;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Refresh Item Slots"))
	void RefreshInventory();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Handle Clicked Button Event"))
	void HandleSlotClick(const FS_Item& ItemData);

};

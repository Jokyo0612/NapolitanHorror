// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DataAssets/S_ItemInfo.h"
#include "NPInvSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class NAPOLITAN_API UNPInvSlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    void UpdateSlot(FName NewItemID, FS_Item* ItemData);

protected:
    UFUNCTION(BlueprintImplementableEvent, Category = "Inventory")
    void BP_UpdateVisuals();

    UPROPERTY(BlueprintReadOnly, Category = "Inventory")
    FName CurrentItemID;

    UPROPERTY(BlueprintReadOnly, Category = "Inventory")
    FS_Item CachedItemData;
};

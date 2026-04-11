// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponentBase.h"
#include "DataAssets/S_ItemInfo.h"
#include "ItemInventoryComponentBase.generated.h"

USTRUCT(BlueprintType)
struct FInventoryArray {
    GENERATED_BODY()

    UPROPERTY()
    TArray<FName> Items;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NAPOLITAN_API UItemInventoryComponentBase : public UPawnExtensionComponentBase
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool AddItem(FName NewItem);

    // 아이템 사용 요청 함수 (UI에서 호출)
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void UseItem(FName ItemToUse);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    const TArray<FName>& GetItems(EItemCategory Category) const;

    FS_Item* GetItemData(FName ItemID) const;

    UFUNCTION(BlueprintPure, Category = "Inventory")
    FS_Item BP_GetItemData(FName ItemID, bool& bSuccess) const;

	TMap<EItemCategory, FInventoryArray> SaveInventory() const;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
    TObjectPtr<UDataTable> ItemDataTable;

    TMap<EItemCategory, FInventoryArray> CategorizedItems;

    virtual void BeginPlay() override;
};

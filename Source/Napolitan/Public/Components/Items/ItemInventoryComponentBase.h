// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponentBase.h"
#include "ItemInventoryComponentBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInventoryUpdated, FName, ItemName);
// DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemUsed, UDataAsset_ItemInfo*, ItemData);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NAPOLITAN_API UItemInventoryComponentBase : public UPawnExtensionComponentBase
{
	GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable, Category = "Inventory|Events")
    FOnInventoryUpdated OnInventoryUpdated;

    //UPROPERTY(BlueprintAssignable, Category = "Inventory|Events")
    //FOnItemUsed OnItemUsed;

    // 아이템 추가 함수
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool AddItem(FName NewItem);

    // 아이템 사용 요청 함수 (UI에서 호출)
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void UseItem(FName ItemToUse);

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
    TObjectPtr<UDataTable> ItemDataTable;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
    TArray<FName> Items;
};

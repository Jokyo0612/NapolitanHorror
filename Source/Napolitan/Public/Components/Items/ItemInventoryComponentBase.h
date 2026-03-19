// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponentBase.h"
#include "ItemInventoryComponentBase.generated.h"

class UDataAsset_ItemInfo;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInventoryUpdated, UDataAsset_ItemInfo*, ItemData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemUsed, UDataAsset_ItemInfo*, ItemData);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NAPOLITAN_API UItemInventoryComponentBase : public UPawnExtensionComponentBase
{
	GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable, Category = "Inventory|Events")
    FOnInventoryUpdated OnInventoryUpdated;

    UPROPERTY(BlueprintAssignable, Category = "Inventory|Events")
    FOnItemUsed OnItemUsed;

    // 아이템 추가 함수
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void AddItem(UDataAsset_ItemInfo* NewItem);

    // 아이템 사용 요청 함수 (UI에서 호출)
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void UseItem(UDataAsset_ItemInfo* ItemToUse);

protected:
    // 실제 데이터를 담을 배열
    UPROPERTY(VisibleAnywhere, Category = "Inventory")
    TArray<UDataAsset_ItemInfo*> Items;
};

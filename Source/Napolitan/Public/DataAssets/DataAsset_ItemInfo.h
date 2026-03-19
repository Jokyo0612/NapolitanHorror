// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_ItemInfo.generated.h"

UENUM(BlueprintType)
enum class EItemCategory : uint8
{
    Usable      UMETA(DisplayName = "Usable Item"),
    Quest       UMETA(DisplayName = "Quest Item"),
    ReadOnly    UMETA(DisplayName = "Read Only")
};
/**
 * 
 */
UCLASS()
class NAPOLITAN_API UDataAsset_ItemInfo : public UDataAsset
{
	GENERATED_BODY()
	
public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemInfo")
    EItemCategory ItemType; // 종류

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemInfo")
    FName ItemID; // 식별 코드

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemInfo")
    FText ItemName; // 이름

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemInfo", meta = (MultiLine = true))
    FText ItemDescription; // 설명

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemInfo")
    TObjectPtr<UTexture2D> ItemIcon; // 인벤토리 아이콘

};

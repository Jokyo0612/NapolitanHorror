#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "S_ItemInfo.generated.h"

UENUM(BlueprintType)
enum class EItemCategory : uint8
{
    Usable      UMETA(DisplayName = "Usable Item"),
    Quest       UMETA(DisplayName = "Quest Item"),
    ReadOnly    UMETA(DisplayName = "Read Only"),
    Equipment   UMETA(DisplayName = "Equipment")
};

USTRUCT(BlueprintType)
struct FS_Item : public FTableRowBase
{

public:

    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemInfo")
    EItemCategory ItemType; // 종류

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemInfo")
    FText ItemName; // 이름

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemInfo", meta = (MultiLine = true))
    FText ItemDescription; // 설명

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemInfo")
    TSoftObjectPtr<UTexture2D> ItemIcon; // 인벤토리 아이콘

};
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "S_ItemInfo.generated.h"

UENUM(BlueprintType)
enum class EItemCategory : uint8
{
	Usable      UMETA(DisplayName = "Usable Item"), // 사용 가능한 아이템 (예: 회복 아이템, 버프 아이템 등)
	Quest       UMETA(DisplayName = "Quest Item"),  // 퀘스트 관련 아이템 (예: 열쇠, 퀘스트 아이템 등)
	ReadOnly    UMETA(DisplayName = "Read Only")    // 읽기 전용 아이템 (예: 수집품, 장식 아이템 등) 
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
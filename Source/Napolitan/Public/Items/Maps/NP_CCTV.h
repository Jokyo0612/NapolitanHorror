// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/NPItemBase.h"
#include "NP_CCTV.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCCTVStateChanged, int32, Clicked_NUM);

/**
 * 
 */
UCLASS()
class NAPOLITAN_API ANP_CCTV : public ANPItemBase
{
	GENERATED_BODY()

	int32 CCTV_Ptr = 0;
	int32 CCTV_ARRAY[3] = { 5, 4, 6 };
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float EventSec;

public:
	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "CCTV")
	FOnCCTVStateChanged OnCCTVStateChanged;

	UFUNCTION(BlueprintCallable, Category = "CCTV")
	bool PuzzleCCTV(int32 Clicked);
};

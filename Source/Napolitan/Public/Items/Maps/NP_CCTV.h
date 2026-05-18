// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/NPItemBase.h"
#include "NP_CCTV.generated.h"

class UNPCH0Component;

/**
 * 
 */
UCLASS()
class NAPOLITAN_API ANP_CCTV : public ANPItemBase
{
	GENERATED_BODY()

	ANP_CCTV();

	int32 CCTV_Ptr = 0;
	int32 CCTV_ARRAY[3] = { 5, 4, 6 };
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CCTV")
	UNPCH0Component* CCTVComponent;

public:
	UFUNCTION(BlueprintCallable, Category = "CCTV")
	bool PuzzleCCTV(int32 Clicked);
};

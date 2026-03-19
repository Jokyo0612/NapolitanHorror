// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InventoryInterface.generated.h"

class UItemInventoryComponentBase;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInventoryInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class NAPOLITAN_API IInventoryInterface
{
	GENERATED_BODY()

public:
	virtual UItemInventoryComponentBase* GetInventoryComponentDefualt() const = 0;
};

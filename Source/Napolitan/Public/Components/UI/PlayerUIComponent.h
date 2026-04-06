// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/UI/PawnUIComponent.h"
#include "PlayerUIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUICalled);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractIconCalled);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractIconRemove);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateSprintMeterDelegate, float, Percentage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSprintStateChangedDelegate, bool, bSprinting);
/**
 * 
 */
UCLASS()
class NAPOLITAN_API UPlayerUIComponent : public UPawnUIComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnInventoryUICalled OnInventoryCalled;

	UPROPERTY(BlueprintAssignable)
	FOnInteractIconCalled OnInteractIconCalled;

	UPROPERTY(BlueprintAssignable)
	FOnInteractIconRemove OnInteractIconRemove;
	
	UPROPERTY(BlueprintAssignable)
	FUpdateSprintMeterDelegate OnSprintMeterUpdated;

	UPROPERTY(BlueprintAssignable)
	FSprintStateChangedDelegate OnSprintStateChanged;
};

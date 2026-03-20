// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/NPInventoryWidgetBase.h"
#include "Interface/InventoryInterface.h"

void UNPInventoryWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (IInventoryInterface* PawnInventoryInterface = Cast<IInventoryInterface>(GetOwningPlayerPawn()))
	{
		if (UItemInventoryComponentBase* PlayerInventoryComponent = PawnInventoryInterface->GetInventoryComponentDefualt())
		{
			BP_OnOwningHeroInventoryComponentInitialized(PlayerInventoryComponent);
		}
	}
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/NPWidgetBase.h"
#include "Interface/PawnUIInterface.h"

void UNPWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(GetOwningPlayerPawn()))
	{
		if (UPlayerUIComponent* PlayerUIComponent = PawnUIInterface->GetPlayerUIComponent())
		{
			BP_OnOwningHeroUIComponentInitialized(PlayerUIComponent);
		}
	}
}


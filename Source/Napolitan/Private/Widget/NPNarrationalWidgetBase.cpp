// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/NPNarrationalWidgetBase.h"
#include "Interface/PawnUIInterface.h"

void UNPNarrationalWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(GetOwningPlayerPawn()))
	{
		if (UNarrationalUIComponent* NarrationUIComponent = PawnUIInterface->GetNarrationUIComponent())
		{
			BP_OnOwningNarrtionUIComponentInitialized(NarrationUIComponent);
		}
	}

}
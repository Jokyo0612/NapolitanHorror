// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/NPWidgetBase.h"
#include "Interface/PawnUIInterface.h"

#include "DebugHelper.h"

void UNPWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Debug::Print(TEXT("Check on 1"));

	if (IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(GetOwningPlayerPawn()))
	{
		Debug::Print(TEXT("Check on 2"));

		if (UPlayerUIComponent* PlayerUIComponent = PawnUIInterface->GetPlayerUIComponent())
		{
			Debug::Print(TEXT("Check on 3"));

			BP_OnOwningHeroUIComponentInitialized(PlayerUIComponent);
		}
	}

}


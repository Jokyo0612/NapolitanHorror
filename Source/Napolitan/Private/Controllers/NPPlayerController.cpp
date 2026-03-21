// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/NPPlayerController.h"
#include "Character/NPPlayerCharacter.h"
#include "Widget/NPWidgetBase.h"
#include "Engine/LocalPlayer.h"
#include "Kismet/GameplayStatics.h"


void ANPPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	// only spawn UI on local player controllers
	if (IsLocalPlayerController())
	{
		// set up the UI for the character
		if (ANPPlayerCharacter* NPCharacter = Cast<ANPPlayerCharacter>(aPawn))
		{
			// create the UI
			if (!DefaultUI)
			{
				DefaultUI = CreateWidget<UNPWidgetBase>(this, DefaultUIClass);
				DefaultUI->AddToViewport(0);
			}
		}
	}
}

void ANPPlayerController::SetUIInputMode(bool bIsUIOpen)
{
	UGameplayStatics::SetGamePaused(GetWorld(), bIsUIOpen);

    if (bIsUIOpen)
    {
		FlushPressedKeys();

        bShowMouseCursor = true;
        FInputModeGameAndUI InputMode;
        InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockInFullscreen);

        SetInputMode(InputMode);
    }
    else
    {
        bShowMouseCursor = false;

        FInputModeGameOnly InputMode;
        SetInputMode(InputMode);
    }
}
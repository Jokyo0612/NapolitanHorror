// Copyright Epic Games, Inc. All Rights Reserved.


#include "NapolitanPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "NapolitanCameraManager.h"
#include "Blueprint/UserWidget.h"
#include "Napolitan.h"
#include "Widgets/Input/SVirtualJoystick.h"

ANapolitanPlayerController::ANapolitanPlayerController()
{
	// set the player camera manager class
	PlayerCameraManagerClass = ANapolitanCameraManager::StaticClass();
}

void ANapolitanPlayerController::BeginPlay()
{
	Super::BeginPlay();

}

void ANapolitanPlayerController::SetupInputComponent()
{

	// only add IMCs for local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Context
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}
		}
	}
	
}
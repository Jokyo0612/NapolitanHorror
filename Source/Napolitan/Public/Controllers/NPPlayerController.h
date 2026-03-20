// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NPPlayerController.generated.h"

class UNPWidgetBase;

/**
 * 
 */
UCLASS()
class NAPOLITAN_API ANPPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, Category = "MainUI")
	TSubclassOf<UNPWidgetBase> DefaultUIClass;

	UPROPERTY()
	TObjectPtr<UNPWidgetBase> DefaultUI;

	virtual void OnPossess(APawn* aPawn) override;
};

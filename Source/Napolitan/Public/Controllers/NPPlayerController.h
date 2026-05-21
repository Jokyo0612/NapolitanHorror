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

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetUIInputMode(bool bIsUIOpen);

protected:
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UNPWidgetBase> DefaultUIClass;

	UPROPERTY(BlueprintReadOnly, Category = "UI")
	TObjectPtr<UNPWidgetBase> DefaultUI;

	virtual void OnPossess(APawn* aPawn) override;
};

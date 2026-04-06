// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gamemodes/NPBaseGamemode.h"
#include "NPTutorialGamemode.generated.h"

/**
 * 
 */
UCLASS()
class NAPOLITAN_API ANPTutorialGamemode : public ANPBaseGamemode
{
	GENERATED_BODY()

protected:
	virtual void PostLogin(APlayerController* NewPlayer) override;

	UFUNCTION(BlueprintCallable)
	void EndTutorialWidget(APlayerController* PC);
};

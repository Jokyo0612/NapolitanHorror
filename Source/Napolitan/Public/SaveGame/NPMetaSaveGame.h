// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "NPGameplayTag.h"
#include "NPMetaSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class NAPOLITAN_API UNPMetaSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly)
	FGameplayTag LastPlayedData;
};

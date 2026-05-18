// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gamemodes/NPBaseGamemode.h"
#include "NPCh0_Gamemode.generated.h"

class UNPCH0Component;

/**
 * 
 */
UCLASS()
class NAPOLITAN_API ANPCh0_Gamemode : public ANPBaseGamemode
{
	GENERATED_BODY()
	
	ANPCh0_Gamemode();	

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CCTV")
	UNPCH0Component* CCTVComponent;
	
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "Gamemodes/NPCh0_Gamemode.h"
#include "Components/StageControll/NPCH0Component.h"

ANPCh0_Gamemode::ANPCh0_Gamemode()
{
	CCTVComponent = CreateDefaultSubobject<UNPCH0Component>(TEXT("CCTVComponent"));
}

void ANPCh0_Gamemode::BeginPlay()
{
	Super::BeginPlay();
}

UNPCH0Component* ANPCh0_Gamemode::GetCh0Component() const
{
	return CCTVComponent;
}

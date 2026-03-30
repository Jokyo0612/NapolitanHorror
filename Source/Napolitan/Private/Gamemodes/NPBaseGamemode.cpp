// Fill out your copyright notice in the Description page of Project Settings.


#include "Gamemodes/NPBaseGamemode.h"

void ANPBaseGamemode::BeginPlay()
{
	Super::BeginPlay();
}

void ANPBaseGamemode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ANPBaseGamemode::SetCurrentGameState(ENPGameState NewState)
{
	CurrentGameState = NewState;

	OnGameStateChanged.Broadcast(CurrentGameState);
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NPGameplayTag.h"
#include "NPBaseGamemode.generated.h"

UENUM(BlueprintType)
enum class ENPGameState : uint8
{
	WaitingToStart UMETA(DisplayName = "Waiting To Start"),
	InProgress UMETA(DisplayName = "In Progress"),
	Paused UMETA(DisplayName = "Paused"),
	GameOver UMETA(DisplayName = "Game Over")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameStateChanged, ENPGameState, CurrentState);

class UNarrationalUIComponent;

/**
 * 
 */
UCLASS()
class NAPOLITAN_API ANPBaseGamemode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	virtual void EndChapter(FGameplayTag NextChapter);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Owning NarrtionUIComponent Initialized"))
	void BP_OnOwningNarrtionUIComponentInitialized(UNarrationalUIComponent* OwningPlayerComponent);

private:
	void SetCurrentGameState(ENPGameState NewState);

	UPROPERTY()
	ENPGameState CurrentGameState;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnGameStateChanged OnGameStateChanged;
};

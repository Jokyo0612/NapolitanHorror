// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/UI/PawnUIComponent.h"
#include "NPGameplayTag.h"
#include "NarrationalUIComponent.generated.h"

class UAudioComponent;
class USoundBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSkipSubscribes);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCallApprove);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCallDenied, FGameplayTag, CallName);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNarrationOn, const FS_Dialogue&, Event_Tag);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNarrationEnded, const FGameplayTag&, Event_Tag);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCallHappened, FGameplayTag, CallNum, float, PlayTime);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnQuestUpdated, FString, SubTitles, float, PlayTime);
/**
 * 
 */
UCLASS()
class NAPOLITAN_API UNarrationalUIComponent : public UPawnUIComponent
{
	GENERATED_BODY()
	
public:
#pragma region Call Events

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FCallHappened CallHappened;
	
	UPROPERTY(BlueprintAssignable)
	FCallApprove CallApprove;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FCallDenied CallDenied;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	FGameplayTag CurrentCallState;

#pragma endregion

#pragma region Narration Events
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnQuestUpdated OnQuestUpdated;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FNarrationOn NarrationOn;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FNarrationEnded NarrationEnded;

	UPROPERTY(BlueprintAssignable)
	FSkipSubscribes SkipSub;

	UPROPERTY(EditAnywhere, Category = "Data")
	UDataTable* NarrationTable;

	FName PendingNextRow;

	FTimerHandle NarrationTimerHandle;

	// Implement later to turn on / off
	UPROPERTY(EditAnywhere, Category = "Data")
	bool bAutoPlayNext;

	void PlayNextDialogue();

	UFUNCTION(BlueprintCallable)
	void TriggerNarration(FName RowName);

	UFUNCTION(BlueprintCallable)
	void SkipNarration();

#pragma endregion

#pragma region Audio Component

	UPROPERTY(VisibleAnywhere, Category = "Audio")
	UAudioComponent* PhoneAudioComponent;

	UFUNCTION(BlueprintCallable, Category = "Event")
	void StopSound();

	UFUNCTION(BlueprintCallable, Category = "Event")
	void StartSound();

protected:
	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* RingingSound;

#pragma endregion

	
};

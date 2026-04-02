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
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNarrationOn, FGameplayTag, Event_Tag);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCallHappened, FGameplayTag, CallNum, float, PlayTime);
/**
 * 
 */
UCLASS()
class NAPOLITAN_API UNarrationalUIComponent : public UPawnUIComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FCallHappened CallHappened;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FNarrationOn NarrationOn;

	UPROPERTY(BlueprintAssignable)
	FCallApprove CallApprove;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FCallDenied CallDenied;

	UPROPERTY(BlueprintAssignable)
	FSkipSubscribes SkipSub;

	UPROPERTY(VisibleAnywhere, Category = "Audio")
	UAudioComponent* PhoneAudioComponent;

	UFUNCTION(BlueprintCallable, Category = "Event")
	void StopSound();

	UFUNCTION(BlueprintCallable, Category = "Event")
	void StartSound();

protected:
	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* RingingSound;

	
};

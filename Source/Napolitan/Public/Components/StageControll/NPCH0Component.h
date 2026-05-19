// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NPCH0Component.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCCTVStateChanged, int32, Clicked_NUM);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCCTVEnded);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRun);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NAPOLITAN_API UNPCH0Component : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float EventSec;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float GroupEventMin;

public:
	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "CCTV")
	FOnCCTVStateChanged OnCCTVStateChanged;

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "CCTV")
	FOnCCTVEnded OnCCTVEnded;

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "CCTV")
	FOnRun OnRun;
};

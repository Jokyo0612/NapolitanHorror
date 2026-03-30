// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "NPFunctionLibrary.generated.h"

class UNPGameInstance;
/**
 * 
 */
UCLASS()
class NAPOLITAN_API UNPFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Napolitan|FunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static UNPGameInstance* GetNPGameInstance(const UObject* WorldContextObject);

};

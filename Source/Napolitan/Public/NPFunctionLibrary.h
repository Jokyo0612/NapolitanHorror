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

#pragma region GameInstance

	UFUNCTION(BlueprintPure, Category = "Napolitan|FunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static UNPGameInstance* GetNPGameInstance(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Napolitan|FunctionLibrary")
	static void SaveInventoryToInstance(const AActor* ContextActor);

#pragma endregion

#pragma region SaveSystem

	UFUNCTION(BlueprintCallable, Category = "Napolitan|FunctionLibrary")
	static void SaveCurrentGameInstance(UNPGameInstance* SaveData, const FGameplayTag& SlotName);

	UFUNCTION(BlueprintCallable, Category = "Napolitan|FunctionLibrary")
	static bool TryLoadGameInstance(UNPGameInstance* LoadData, const FGameplayTag& SlotName);

	UFUNCTION(BlueprintCallable, Category = "Napolitan|FunctionLibrary")
	static void DeleteSaveData(const FGameplayTag& SlotName);

	UFUNCTION(BlueprintPure, Category = "Napolitan|FunctionLibrary")
	static FGameplayTag GetLastSaveData();

	UFUNCTION(BlueprintCallable, Category = "Napolitan|FunctionLibrary")
	static void SetLastSaveData(const FGameplayTag& SlotName);

	UFUNCTION(BlueprintCallable, Category = "Napolitan|FunctionLibrary")
	static FGameplayTag FindFirstEmptySlotIndex(int32 MaxSlots = 5);

	UFUNCTION(BlueprintCallable, Category = "Napolitan|FunctionLibrary")
	static FGameplayTag GetSaveSlotSummary(FGameplayTag SlotTag);

#pragma endregion

};

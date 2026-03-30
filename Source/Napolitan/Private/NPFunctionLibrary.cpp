// Fill out your copyright notice in the Description page of Project Settings.


#include "NPFunctionLibrary.h"
#include "NPGameInstance.h"

UNPGameInstance* UNPFunctionLibrary::GetNPGameInstance(const UObject* WorldContextObject)
{
	if (GEngine)
	{
		if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
		{
			return World->GetGameInstance<UNPGameInstance>();
		}
	}

	return nullptr;
}

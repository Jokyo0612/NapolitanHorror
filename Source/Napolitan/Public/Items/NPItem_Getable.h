// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/NPItemBase.h"
#include "NPItem_Getable.generated.h"

/**
 * 
 */
UCLASS()
class NAPOLITAN_API ANPItem_Getable : public ANPItemBase
{
	GENERATED_BODY()
	
	void Interact_Implementation(AActor* Interactor) override;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "StageControlInterface.generated.h"

class UNPCH0Component;

UINTERFACE(MinimalAPI)
class UStageControlInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class NAPOLITAN_API IStageControlInterface
{
	GENERATED_BODY()

public:
	virtual UNPCH0Component* GetCh0Component() const;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/PawnUIInterface.h"
#include "NPBaseCharacter.generated.h"

class UPawnUIComponent;

UCLASS()
class NAPOLITAN_API ANPBaseCharacter : public ACharacter, public IPawnUIInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPBaseCharacter();

	virtual UPawnUIComponent* GetPawnUIComponent() const override;

	virtual void PossessedBy(AController* NewController) override;
};

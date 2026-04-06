// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "DialogueByTag.generated.h"


USTRUCT(BlueprintType)
struct FS_Dialogue : public FTableRowBase
{

public:

    GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag CurrentDialogue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DialogueText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText WhoTalk;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName NextRowName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ManualDuration = 0.f;

	float GetDisplayDuration() const;

};
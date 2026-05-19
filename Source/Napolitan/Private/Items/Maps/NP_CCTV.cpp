// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Maps/NP_CCTV.h"
#include "Components/StageControll/NPCH0Component.h"
#include "Interface/StageControlInterface.h"
#include "GameFramework/GameModeBase.h"

void ANP_CCTV::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld() && GetWorld()->GetAuthGameMode())
	{
		if (IStageControlInterface* StageControlInterface = Cast<IStageControlInterface>(GetWorld()->GetAuthGameMode()))
		{
			CCTVComponent = StageControlInterface->GetCh0Component();
		}
	}
}

bool ANP_CCTV::PuzzleCCTV(int32 Clicked)
{
	if (CCTV_ARRAY[CCTV_Ptr] == Clicked)
	{
		CCTVComponent->OnCCTVStateChanged.Broadcast(CCTV_Ptr);
		CCTV_Ptr++;

		if (CCTV_Ptr >= 3)
		{
			CCTVComponent->OnCCTVEnded.Broadcast();

		return true;
		}
	}
	else if (Clicked == 3)
	{
		CCTVComponent->OnCCTVStateChanged.Broadcast(CCTV_Ptr);
	}

	return false;
}

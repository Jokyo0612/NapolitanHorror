// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Maps/NP_CCTV.h"

bool ANP_CCTV::PuzzleCCTV(int32 Clicked)
{
	if (CCTV_ARRAY[CCTV_Ptr] == Clicked)
	{
		OnCCTVStateChanged.Broadcast(CCTV_Ptr);
		CCTV_Ptr++;

		if (CCTV_Ptr >= 3)
		{
			OnCCTVStateChanged.Broadcast(CCTV_Ptr);
		}

		return true;
	}
	else if (Clicked == 3)
	{
		OnCCTVStateChanged.Broadcast(CCTV_Ptr);
	}

	return false;
}

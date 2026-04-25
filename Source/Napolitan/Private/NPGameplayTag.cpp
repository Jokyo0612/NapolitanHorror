// Fill out your copyright notice in the Description page of Project Settings.


#include "NPGameplayTag.h"

namespace NPGamplayTags
{
	/** Input Tags */ 
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "InputTag.Look");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Jump, "InputTag.Jump");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Crouch, "InputTag.Crouch");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Sprint, "InputTag.Sprint");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Interact, "InputTag.Interact");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_ItemListCall, "InputTag.ItemListCall");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_NextSentence, "InputTag.NextSentence");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_PhoneCall, "InputTag.PhoneCall");

	/** Chapter Tags */
	UE_DEFINE_GAMEPLAY_TAG(Chapter_Option_MainMenu, "Chapter.Option.MainMenu");
	UE_DEFINE_GAMEPLAY_TAG(Chapter_00_Room, "Chapter.00.Room");
	UE_DEFINE_GAMEPLAY_TAG(Chapter_00_Warehouse, "Chapter.00.Warehouse");
	UE_DEFINE_GAMEPLAY_TAG(Chapter_00_MonitorRoom, "Chapter.00.MonitorRoom");

	/** Call Tags */
	UE_DEFINE_GAMEPLAY_TAG(Call_00_Tutorial, "Call.00.Tutorial");

	/** Subscribes Tags */
	UE_DEFINE_GAMEPLAY_TAG(Sub_00_Room, "Sub.00.Room");
	UE_DEFINE_GAMEPLAY_TAG(Sub_00_Room2, "Sub.00.Room2");
	UE_DEFINE_GAMEPLAY_TAG(Sub_00_Start, "Sub.00.Start");
	UE_DEFINE_GAMEPLAY_TAG(Sub_00_GuideMet, "Sub.00.GuideMet");
	UE_DEFINE_GAMEPLAY_TAG(Sub_00_GuideMet2, "Sub.00.GuideMet2");
	UE_DEFINE_GAMEPLAY_TAG(Sub_00_Video, "Sub.00.Video");

	/** Rejection SubTags */
	UE_DEFINE_GAMEPLAY_TAG(Sub_Reject_00, "Sub.Reject.00");
	UE_DEFINE_GAMEPLAY_TAG(Sub_Reject_01, "Sub.Reject.01");
	UE_DEFINE_GAMEPLAY_TAG(Sub_Reject_02, "Sub.Reject.02");

	/** States Tags */
	UE_DEFINE_GAMEPLAY_TAG(State_Call_Busy, "State.Call.Busy");
	UE_DEFINE_GAMEPLAY_TAG(State_Call_Allow, "State.Call.Allow");

	/** Event Tags */
	UE_DEFINE_GAMEPLAY_TAG(Event_Watched_TutorialVideo, "Event.Watched.TutorialVideo");

	/** Game Data Tags */
	UE_DEFINE_GAMEPLAY_TAG(GameData_SaveGame_MetaData, "GameData.SaveGame.MetaData");
	UE_DEFINE_GAMEPLAY_TAG(GameData_SaveGame_Slot_1, "GameData.SaveGame.Slot.1");
	UE_DEFINE_GAMEPLAY_TAG(GameData_SaveGame_Slot_2, "GameData.SaveGame.Slot.2");
	UE_DEFINE_GAMEPLAY_TAG(GameData_SaveGame_Slot_3, "GameData.SaveGame.Slot.3");
	UE_DEFINE_GAMEPLAY_TAG(GameData_SaveGame_Slot_4, "GameData.SaveGame.Slot.4");
	UE_DEFINE_GAMEPLAY_TAG(GameData_SaveGame_Slot_5, "GameData.SaveGame.Slot.5");
}
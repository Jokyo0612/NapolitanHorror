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

	/** Chapter Tags */
	UE_DEFINE_GAMEPLAY_TAG(Chapter_Option_MainMenu, "Chapter.Option.MainMenu");
	UE_DEFINE_GAMEPLAY_TAG(Chapter_00_Room, "Chapter.00.Room");
	UE_DEFINE_GAMEPLAY_TAG(Chapter_00_Warehouse, "Chapter.00.Warehouse");
	
}
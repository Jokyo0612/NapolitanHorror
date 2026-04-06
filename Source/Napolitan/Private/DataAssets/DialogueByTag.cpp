// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/DialogueByTag.h"

float FS_Dialogue::GetDisplayDuration() const
{
    if (ManualDuration > 0.f) return ManualDuration;

    int32 CharCount = DialogueText.ToString().Len();

    return (CharCount * 0.2f) + 1.0f;
}

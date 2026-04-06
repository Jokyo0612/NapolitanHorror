// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/UI/NarrationalUIComponent.h"
#include "Components/AudioComponent.h"
#include "DataAssets/DialogueByTag.h"


void UNarrationalUIComponent::TriggerNarration(FName RowName)
{
    if (!NarrationTable) return;

    FS_Dialogue* Data = NarrationTable->FindRow<FS_Dialogue>(RowName, TEXT(""));

    if (Data)
    {
        NarrationOn.Broadcast(*Data);

        PendingNextRow = Data->NextRowName;

        GetWorld()->GetTimerManager().ClearTimer(NarrationTimerHandle);

        if (bAutoPlayNext)
        {
            float CalculatedDuration = Data->GetDisplayDuration();

            if (!PendingNextRow.IsNone())
            {
                GetWorld()->GetTimerManager().SetTimer(
                    NarrationTimerHandle,
                    this,
                    &UNarrationalUIComponent::PlayNextDialogue,
                    CalculatedDuration,
                    false
                );
            }
        }
        
    }
}

void UNarrationalUIComponent::SkipNarration()
{
    GetWorld()->GetTimerManager().ClearTimer(NarrationTimerHandle);

    if (!PendingNextRow.IsNone())
    {
		PlayNextDialogue();
    }
}

void UNarrationalUIComponent::PlayNextDialogue()
{
    TriggerNarration(PendingNextRow);
}

void UNarrationalUIComponent::StartSound()
{
    if (PhoneAudioComponent && RingingSound)
    {
        PhoneAudioComponent->SetSound(RingingSound);
        PhoneAudioComponent->Play();
    }
}

void UNarrationalUIComponent::StopSound()
{
    if (PhoneAudioComponent->IsPlaying())
    {
        PhoneAudioComponent->Stop();
    }
}
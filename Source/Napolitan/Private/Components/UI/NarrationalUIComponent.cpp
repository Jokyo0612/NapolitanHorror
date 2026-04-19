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
            float CalculatedDuration = 0.f; 
            if (Data->ManualDuration > 0.f) { CalculatedDuration = Data->ManualDuration;}
            else { CalculatedDuration = Data->GetDisplayDuration();}

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
            else 
            {
                FTimerDelegate TimerDelegate;
                TimerDelegate.BindUObject(this, &UNarrationalUIComponent::EndCurrentDialogue, Data->CurrentDialogue);

                GetWorld()->GetTimerManager().SetTimer(
                    NarrationTimerHandle,
                    TimerDelegate,
                    CalculatedDuration,
                    false
                );
            }
        }
        
    }
}

void UNarrationalUIComponent::SkipNarration(FGameplayTag EventTag)
{
    GetWorld()->GetTimerManager().ClearTimer(NarrationTimerHandle);

    if (!PendingNextRow.IsNone())
    {
		PlayNextDialogue();
    }
    else 
    {
		EndCurrentDialogue(EventTag);
    }
}

void UNarrationalUIComponent::PlayNextDialogue()
{
    TriggerNarration(PendingNextRow);
}

void UNarrationalUIComponent::EndCurrentDialogue(FGameplayTag EventTag)
{
	NarrationEnded.Broadcast(EventTag);
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
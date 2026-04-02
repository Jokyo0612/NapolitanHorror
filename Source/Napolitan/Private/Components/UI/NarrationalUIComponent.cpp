// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/UI/NarrationalUIComponent.h"
#include "Components/AudioComponent.h"

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
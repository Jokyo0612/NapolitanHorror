// Fill out your copyright notice in the Description page of Project Settings.


#include "Gamemodes/NPTutorialGamemode.h"
#include "Kismet/GameplayStatics.h"

void ANPTutorialGamemode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    TArray<AActor*> FoundCameras;
    UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("TutorialCamera"), FoundCameras);

    if (FoundCameras.Num() > 0 && NewPlayer)
    {
        NewPlayer->SetViewTarget(FoundCameras[0]);

        NewPlayer->bShowMouseCursor = true;
        FInputModeUIOnly InputMode;
        NewPlayer->SetInputMode(InputMode);
    }
}

void ANPTutorialGamemode::EndTutorial(APlayerController* PC)
{
    if (PC && PC->GetPawn())
    {
        PC->SetViewTargetWithBlend(PC->GetPawn(), 2.0f, EViewTargetBlendFunction::VTBlend_Cubic);

        PC->bShowMouseCursor = false;
        FInputModeGameOnly InputMode;
        PC->SetInputMode(InputMode);
    }
}
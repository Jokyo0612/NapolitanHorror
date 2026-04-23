// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractUIComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

UInteractUIComponent::UInteractUIComponent()
{
    PrimaryComponentTick.bCanEverTick = false;

    InteractIconWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractIcon"));
    InteractIconWidget->SetWidgetSpace(EWidgetSpace::Screen);
    InteractIconWidget->SetVisibility(false);
    InteractIconWidget->SetDrawSize(FVector2D(50.0f, 50.0f));

    DetectSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DetectSphere"));
    DetectSphere->OnComponentBeginOverlap.AddDynamic(this, &UInteractUIComponent::OnDetectBeginOverlap);
    DetectSphere->OnComponentEndOverlap.AddDynamic(this, &UInteractUIComponent::OnDetectEndOverlap);

    static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClassFinder(TEXT("/Game/Widget/Event/WBP_InteractionCheck.WBP_InteractionCheck_C"));
    if (WidgetClassFinder.Succeeded())
    {
        InteractIconWidget->SetWidgetClass(WidgetClassFinder.Class);
    }
}

void UInteractUIComponent::OnRegister()
{
    Super::OnRegister();
    UpdateIconPosition();
}

void UInteractUIComponent::UpdateIconPosition()
{
    AActor* Owner = GetOwner();

    if (!Owner || !InteractIconWidget) return;

    UBoxComponent* OwnerBox = Owner->FindComponentByClass<UBoxComponent>();

    if (OwnerBox)
    {
        float BoxHalfHeight = OwnerBox->GetScaledBoxExtent().Z;
        float BoxTopZ = OwnerBox->GetRelativeLocation().Z + BoxHalfHeight;

		InteractIconWidget->SetupAttachment(this);
        InteractIconWidget->SetRelativeLocation(FVector(0.f, 0.f, BoxTopZ + IconZOffset));

		DetectSphere->SetupAttachment(this);
        DetectSphere->SetSphereRadius(SphereRadius);
    }
}

void UInteractUIComponent::HideIcon()
{
    if (InteractIconWidget)
    {
        InteractIconWidget->SetVisibility(false);
	}
}

void UInteractUIComponent::OnDetectBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor->IsA(APawn::StaticClass()))
    {
        if (bInteractable) { InteractIconWidget->SetVisibility(true); }
    }
}

void UInteractUIComponent::OnDetectEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor && OtherActor->IsA(APawn::StaticClass()))
    {
        InteractIconWidget->SetVisibility(false);
    }
}
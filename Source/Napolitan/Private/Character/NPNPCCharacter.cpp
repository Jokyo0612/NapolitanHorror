// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NPNPCCharacter.h"
#include "Interface/PawnUIInterface.h"
#include "Interface/InventoryInterface.h"
#include "Components/UI/NarrationalUIComponent.h"
#include "Components/InteractUIComponent.h"
#include "Components/BoxComponent.h"

ANPNPCCharacter::ANPNPCCharacter()
{
    PrimaryActorTick.bCanEverTick = false;

    ItemCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ItemCollisionBox"));
    ItemCollisionBox->SetupAttachment(GetRootComponent());
    ItemCollisionBox->SetBoxExtent(FVector(20.f));
    ItemCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    // Channel allocation for line trace
    ItemCollisionBox->SetCollisionResponseToAllChannels(ECR_Ignore);
    ItemCollisionBox->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
    // Camera Collision Ignore
    ItemCollisionBox->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	// Interaction Icon and Detection Sphere
    InteractionHandler = CreateDefaultSubobject<UInteractUIComponent>(TEXT("InteractionHandler"));
	InteractionHandler->SetupAttachment(RootComponent);
}

void ANPNPCCharacter::Interact_Implementation(AActor* Interactor)
{
    if (!Interactor || !InteractionHandler->bInteractable) return;

    if (InteractionHandler->bInteractable)
    {
		InteractionHandler->bInteractable = false;

        IPawnUIInterface* PawnUI = Cast<IPawnUIInterface>(Interactor);
        IInventoryInterface* PawnInv = Cast<IInventoryInterface>(Interactor);

        if (PawnUI && PawnInv)
        {
            UNarrationalUIComponent* NarrationComp = PawnUI->GetNarrationUIComponent();
            UItemInventoryComponentBase* Inventory = PawnInv->GetInventoryComponentDefualt();

            if (NarrationComp && Inventory)
            {
                BP_OnNPCInteractionCalled(NarrationComp, Inventory);
            }
        }
    }

}

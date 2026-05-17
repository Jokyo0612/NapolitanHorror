// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/NPItemBase.h"
#include "Components/BoxComponent.h"
#include "Components/InteractUIComponent.h"

ANPItemBase::ANPItemBase()
{
	PrimaryActorTick.bCanEverTick = false;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->bRenderCustomDepth = true;
	ItemMesh->CustomDepthStencilValue = 1;
	SetRootComponent(ItemMesh);

	ItemCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ItemCollisionBox"));
	ItemCollisionBox->SetupAttachment(GetRootComponent());
	ItemCollisionBox->SetBoxExtent(FVector(20.f));
	// No Physics Option
	ItemCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	// Channel allocation for line trace
	ItemCollisionBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	ItemCollisionBox->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	// Camera Collision Ignore
	ItemCollisionBox->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	// Detection Sphere
	InteractionHandler = CreateDefaultSubobject<UInteractUIComponent>(TEXT("InteractionHandler"));
	InteractionHandler->SetupAttachment(RootComponent);
}

void ANPItemBase::Interact_Implementation(AActor* Interactor)
{
	if (!Interactor || !InteractionHandler->bInteractable) return;
}

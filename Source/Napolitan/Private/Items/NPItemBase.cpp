// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/NPItemBase.h"
#include "DataAssets/DataAsset_ItemInfo.h"
#include "Components/BoxComponent.h"
#include "DebugHelper.h"

// Sets default values
ANPItemBase::ANPItemBase()
{
	PrimaryActorTick.bCanEverTick = false;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
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
}

void ANPItemBase::Interact_Implementation(AActor* Interactor)
{
	// if (ItemData == nullptr) return;
	Debug::Print(TEXT("Interact Succeed"));
	return;
}

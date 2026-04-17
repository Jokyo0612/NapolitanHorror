// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/NPItemBase.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
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
	DetectSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DetectSphere"));
	DetectSphere->SetupAttachment(RootComponent);
	DetectSphere->SetSphereRadius(SphereRadius);

	InteractIconWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractIcon"));
	InteractIconWidget->SetupAttachment(RootComponent);
	InteractIconWidget->SetWidgetSpace(EWidgetSpace::Screen);
	InteractIconWidget->SetVisibility(false);
	InteractIconWidget->SetDrawSize(FVector2D(50.0f, 50.0f));

	DetectSphere->OnComponentBeginOverlap.AddDynamic(this, &ANPItemBase::OnDetectBeginOverlap);
	DetectSphere->OnComponentEndOverlap.AddDynamic(this, &ANPItemBase::OnDetectEndOverlap);
}

void ANPItemBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (ItemCollisionBox && InteractIconWidget)
	{
		float BoxHalfHeight = ItemCollisionBox->GetScaledBoxExtent().Z;
		float BoxTopZ = ItemCollisionBox->GetRelativeLocation().Z + BoxHalfHeight;
		float FinalOffset = BoxTopZ + IconZOffset;

		InteractIconWidget->SetRelativeLocation(FVector(0.f, 0.f, FinalOffset));
	}
}

void ANPItemBase::OnDetectBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->IsA(APawn::StaticClass()))
	{
		InteractIconWidget->SetVisibility(true);
	}
}

void ANPItemBase::OnDetectEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor->IsA(APawn::StaticClass()))
	{
		InteractIconWidget->SetVisibility(false);
	}
}

void ANPItemBase::Interact_Implementation(AActor* Interactor)
{
	return;
}

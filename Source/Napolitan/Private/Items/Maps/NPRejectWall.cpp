
#include "Items/Maps/NPRejectWall.h"
#include "Components/BoxComponent.h"
#include "Interface/PawnUIInterface.h"

ANPRejectWall::ANPRejectWall()
{
	PrimaryActorTick.bCanEverTick = true;

	ItemCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ItemCollisionBox"));
	ItemCollisionBox->SetupAttachment(GetRootComponent());
	ItemCollisionBox->SetBoxExtent(FVector(20.f));
	// No Physics Option
	ItemCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	// Camera Collision Ignore
	ItemCollisionBox->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	ItemCollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);

	ItemCollisionBox->OnComponentHit.AddDynamic(this, &ANPRejectWall::OnComponentHit);
}

void ANPRejectWall::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!OtherActor) return;

	IPawnUIInterface* Interface = Cast<IPawnUIInterface>(OtherActor);

	if (Interface)
	{
		BP_OnPlayerDetected(Interface->GetNarrationUIComponent());
	}
}
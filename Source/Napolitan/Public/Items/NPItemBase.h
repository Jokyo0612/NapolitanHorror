// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/InteractInterface.h"
#include "NPItemBase.generated.h"

class UDataAsset_ItemInfo;
class UBoxComponent;

UCLASS()
class NAPOLITAN_API ANPItemBase : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:
	ANPItemBase();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Items")
	TObjectPtr<UDataAsset_ItemInfo> ItemData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items")
	TObjectPtr<UStaticMeshComponent> ItemMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapones")
	UBoxComponent* ItemCollisionBox;

	void Interact_Implementation(AActor* Interactor) override;

};

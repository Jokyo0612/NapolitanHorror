// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "Interface/InteractInterface.h"
#include "NPItemBase.generated.h"

class UBoxComponent;

UCLASS()
class NAPOLITAN_API ANPItemBase : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:
	ANPItemBase();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FDataTableRowHandle ItemHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items")
	TObjectPtr<UStaticMeshComponent> ItemMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items")
	UBoxComponent* ItemCollisionBox;

	void Interact_Implementation(AActor* Interactor) override;

};

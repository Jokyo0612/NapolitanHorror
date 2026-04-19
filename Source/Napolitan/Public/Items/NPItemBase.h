// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "Interface/InteractInterface.h"
#include "NPItemBase.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UInteractUIComponent;

UCLASS()
class NAPOLITAN_API ANPItemBase : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:
	ANPItemBase();

protected:

#pragma region Interaction UI

	UPROPERTY(VisibleAnywhere, Category = "Interaction")
	TObjectPtr<class UInteractUIComponent> InteractionHandler;

#pragma endregion

#pragma region Item Data

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FDataTableRowHandle ItemHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items")
	TObjectPtr<UStaticMeshComponent> ItemMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items")
	TObjectPtr<UBoxComponent> ItemCollisionBox;

	void Interact_Implementation(AActor* Interactor) override;

#pragma endregion

};

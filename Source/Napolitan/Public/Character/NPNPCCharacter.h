// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/NPBaseCharacter.h"
#include "Interface/InteractInterface.h"
#include "NPNPCCharacter.generated.h"

class UNarrationalUIComponent;
class UItemInventoryComponentBase;
class UInteractUIComponent;
class UBoxComponent;
class UStaticMeshComponent;

/**
 * 
 */
UCLASS()
class NAPOLITAN_API ANPNPCCharacter : public ANPBaseCharacter, public IInteractInterface
{
	GENERATED_BODY()

public:
	ANPNPCCharacter();

protected:
	void Interact_Implementation(AActor* Interactor) override;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On NPC Interact Event"))
	void BP_OnNPCInteractionCalled(UNarrationalUIComponent* OwningPlayerComponent, UItemInventoryComponentBase* Inv);
	
	UPROPERTY(VisibleAnywhere, Category = "Interaction")
	TObjectPtr<class UInteractUIComponent> InteractionHandler;

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void HideInteractionIcon();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> ItemCollisionBox;

};

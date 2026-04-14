// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "Interface/InteractInterface.h"
#include "NPItemBase.generated.h"

class UBoxComponent;
class UWidgetComponent;
class USphereComponent;

UCLASS()
class NAPOLITAN_API ANPItemBase : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:
	ANPItemBase();

protected:

#pragma region Interaction UI

	UPROPERTY(VisibleAnywhere, Category = "UI")
	TObjectPtr<UWidgetComponent> InteractIconWidget;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	TObjectPtr<USphereComponent> DetectSphere;

	UPROPERTY(EditAnywhere, Category = "UI")
	float InteractIconZOffset = 200.0f;

	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION()
	void OnDetectBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnDetectEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

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

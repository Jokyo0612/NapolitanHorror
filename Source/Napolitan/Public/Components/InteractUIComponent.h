// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "InteractUIComponent.generated.h"

class UWidgetComponent;
class USphereComponent;

/**
 * 
 */
UCLASS()
class NAPOLITAN_API UInteractUIComponent : public USceneComponent
{
	GENERATED_BODY()
	
public:
    UInteractUIComponent();

    // UI Components
    UPROPERTY(VisibleAnywhere, Category = "Interaction")
    TObjectPtr<class UWidgetComponent> InteractIconWidget;

    UPROPERTY(VisibleAnywhere, Category = "Interaction")
    TObjectPtr<class USphereComponent> DetectSphere;

    UPROPERTY(EditAnywhere, Category = "Interaction")
    bool bInteractable = true;

    void HideIcon();

protected:
    virtual void OnRegister() override;

	// Variables
    UPROPERTY(EditAnywhere, Category = "Interaction")
    float IconZOffset = 30.f;

    UPROPERTY(EditAnywhere, Category = "Interaction")
    float SphereRadius = 800.f;

    void UpdateIconPosition();

    // Detection Functions
    UFUNCTION()
    void OnDetectBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnDetectEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NP_AfterCCTV.generated.h"

class UNPCH0Component;
class UBoxComponent;

UCLASS()
class NAPOLITAN_API ANP_AfterCCTV : public AActor
{
	GENERATED_BODY()
	
	ANP_AfterCCTV();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CCTV")
	UNPCH0Component* CCTVComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items")
	TObjectPtr<UBoxComponent> ItemCollisionBox;

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapDarkWall(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintImplementableEvent)
	void StartEvent();
};

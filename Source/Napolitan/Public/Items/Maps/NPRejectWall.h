// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NPRejectWall.generated.h"

class UBoxComponent;
class UNarrationalUIComponent;

UCLASS()
class NAPOLITAN_API ANPRejectWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANPRejectWall();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items")
	TObjectPtr<UBoxComponent> ItemCollisionBox;

	UFUNCTION()
	void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintImplementableEvent, Category = "Rejection Wall")
	void BP_OnPlayerDetected(UNarrationalUIComponent* NarrationUIComponent);
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/NPBaseCharacter.h"
#include "Interface/InteractInterface.h"
#include "Interface/InventoryInterface.h"
#include "NPPlayerCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;
class USpotLightComponent;
class UDataAsset_InputConfig;
class UPawnUIComponent;
class UPlayerUIComponent;
class UNarrationalUIComponent;

/**
 * 
 */
UCLASS()
class NAPOLITAN_API ANPPlayerCharacter : public ANPBaseCharacter, public IInteractInterface, public IInventoryInterface
{
	GENERATED_BODY()

#pragma region Character_Appearance

	/* 1ÀÎÄª¿ë ¸Þ½Ã */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* FirstPersonMesh;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	FVector DefaultCameraLoc = FVector(-2.8f, 5.89f, 64.0f);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpotLightComponent* SpotLight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	UItemInventoryComponentBase* PlayerInventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UPlayerUIComponent* PlayerUIComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UNarrationalUIComponent* NarrationComponent;

protected:

	ANPPlayerCharacter();

	/** Gameplay initialization */
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	/** Gameplay cleanup */
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

	/** Set up input action bindings */
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;


public:

	/** Returns the first person mesh **/
	USkeletalMeshComponent* GetFirstPersonMesh() const { return FirstPersonMesh; }

	/** Returns first person camera component **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

#pragma endregion

#pragma region Input_parameters

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
	UDataAsset_InputConfig* InputConfigDataAsset;

protected:
	UPROPERTY(EditAnywhere, Category = "Walk")
	float WalkSpeed = 250.0f;

	UPROPERTY(EditAnywhere, Category = "Walk")
	float CrouchSpeed = 100.0f;

	/** If true, we're sprinting */
	bool bSprinting = false;

	/** If true, we're recovering stamina */
	bool bRecovering = false;

	/** Time interval for sprinting stamina ticks */
	UPROPERTY(EditAnywhere, Category = "Sprint", meta = (ClampMin = 0, ClampMax = 1, Units = "s"))
	float SprintFixedTickTime = 0.03333f;

	/** Sprint stamina amount. Maxes at SprintTime */
	float SprintMeter = 0.0f;

	/** How long we can sprint for, in seconds */
	UPROPERTY(EditAnywhere, Category = "Sprint", meta = (ClampMin = 0, ClampMax = 10, Units = "s"))
	float SprintTime = 3.0f;

	/** Walk speed while sprinting */
	UPROPERTY(EditAnywhere, Category = "Sprint", meta = (ClampMin = 0, ClampMax = 10, Units = "cm/s"))
	float SprintSpeed = 600.0f;

	/** Walk speed while recovering stamina */
	UPROPERTY(EditAnywhere, Category = "Recovery", meta = (ClampMin = 0, ClampMax = 10, Units = "cm/s"))
	float RecoveringWalkSpeed = 150.0f;

	/** Time it takes for the sprint meter to recover */
	UPROPERTY(EditAnywhere, Category = "Recovery", meta = (ClampMin = 0, ClampMax = 10, Units = "s"))
	float RecoveryTime = 0.0f;

	/** Sprint tick timer */
	FTimerHandle SprintTimer;

#pragma endregion

#pragma region Input_functions

	/** Called from Input Actions for movement input */
	void MoveInput(const FInputActionValue& Value);

	/** Called from Input Actions for looking input */
	void LookInput(const FInputActionValue& Value);

	/** Handles aim inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoAim(float Yaw, float Pitch);

	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);

	/** Handles jump start inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpStart();

	/** Handles jump end inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpEnd();

	/** Handle Crouch inputs with other actions */
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoCrouchStart();

	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoCrouchEnd();

	virtual void OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	virtual void OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;

	/* Crouch Control after falling */ 
	bool bWantsToCrouchBuffer = false;
	virtual void Landed(const FHitResult& Hit) override;

	/** Starts sprinting behavior */
	UFUNCTION(BlueprintCallable, Category = "Input")
	void DoStartSprint();

	/** Stops sprinting behavior */
	UFUNCTION(BlueprintCallable, Category = "Input")
	void DoEndSprint();

	/** Called while sprinting at a fixed time interval */
	void SprintFixedTick();

	/** Go to Next Event Talk */
	UFUNCTION(BlueprintCallable, Category = "Input")
	void Next_Sentence();

	/** Get a Phone Call */
	UFUNCTION(BlueprintCallable, Category = "Input")
	void Get_Phone();

#pragma endregion

#pragma region Input_Interact
	// Timer 0.1 sec instead of Tick
	FTimerHandle TimerHandle_Interaction;

	UPROPERTY(VisibleInstanceOnly, Category = "Interaction")
	TObjectPtr<AActor> TargetActor;

	void PerformInteractionCheck();

	void Interact();

#pragma endregion

#pragma region UI_Inventory
public:
	//~Begin IInventory Interface
	virtual UItemInventoryComponentBase* GetInventoryComponentDefualt() const override;
	//~End IInventory Interface

	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	virtual UPlayerUIComponent* GetPlayerUIComponent() const override;

	UFUNCTION(BlueprintCallable, Category = "Input")
	void ItemListCall();

protected:
	float LastUICallTime = 0.0f;
	float UICallCooldown = 1.5f;

#pragma endregion

#pragma region Subscribe
public:
	virtual UNarrationalUIComponent* GetNarrationUIComponent() const override;

};


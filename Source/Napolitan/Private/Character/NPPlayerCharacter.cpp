// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NPPlayerCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SpotLightComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "DataAssets/DataAsset_InputConfig.h"
#include "Components/Input/NPInputComponent.h"
#include "Components/Items/ItemInventoryComponentBase.h"
#include "Components/UI/PlayerUIComponent.h"
#include "Components/UI/NarrationalUIComponent.h"
#include "Components/AudioComponent.h"
#include "NPGameplayTag.h"

#include "DebugHelper.h"

ANPPlayerCharacter::ANPPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(34.f, 96.0f);

	// Camera Spring Arm
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetCapsuleComponent());
	CameraBoom->TargetArmLength = 0.0f;
	CameraBoom->SetRelativeLocation(DefaultCameraLoc);
	CameraBoom->bUsePawnControlRotation = true;

	// Camera Collision Manager 
	CameraBoom->bDoCollisionTest = true;
	CameraBoom->ProbeSize = 5.0f;
	CameraBoom->ProbeChannel = ECC_Camera;

	// Camera Component
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	FirstPersonCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FirstPersonCameraComponent->bUsePawnControlRotation = false;
	FirstPersonCameraComponent->bEnableFirstPersonFieldOfView = true;
	FirstPersonCameraComponent->FirstPersonFieldOfView = 70.0f;
	FirstPersonCameraComponent->bEnableFirstPersonScale = true;
	FirstPersonCameraComponent->FirstPersonScale = 0.6f;

	// 1인칭 화면용 메시
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("First Person Mesh"));
	FirstPersonMesh->SetupAttachment(FirstPersonCameraComponent);
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;
	FirstPersonMesh->SetCollisionProfileName(FName("NoCollision"));

	// create the spotlight
	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	SpotLight->SetupAttachment(GetFirstPersonCameraComponent());

	SpotLight->SetRelativeLocationAndRotation(FVector(30.0f, 17.5f, -5.0f), FRotator(-18.6f, -1.3f, 5.26f));
	SpotLight->Intensity = 0.5;
	SpotLight->SetIntensityUnits(ELightUnits::Lumens);
	SpotLight->AttenuationRadius = 1050.0f;
	SpotLight->InnerConeAngle = 18.7f;
	SpotLight->OuterConeAngle = 45.24f;

	// 간접 표시용 메시
	GetMesh()->SetOwnerNoSee(true);
	GetMesh()->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::WorldSpaceRepresentation;

	// Configure character movement
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	GetCharacterMovement()->AirControl = 0.5f;
	GetCharacterMovement()->MaxWalkSpeedCrouched = CrouchSpeed;

	// Inventory
	PlayerInventoryComponent = CreateDefaultSubobject<UItemInventoryComponentBase>(TEXT("PlayerInventoryComponent"));
	PlayerUIComponent = CreateDefaultSubobject<UPlayerUIComponent>(TEXT("PlayerUIComponent"));

	// Subscribe Bar
	NarrationComponent = CreateDefaultSubobject<UNarrationalUIComponent>(TEXT("NarrationComponent"));
	NarrationComponent->PhoneAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("PhoneAudioComponent"));
	NarrationComponent->PhoneAudioComponent->SetupAttachment(GetRootComponent());
	NarrationComponent->PhoneAudioComponent->bAutoActivate = false;
}

void ANPPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// initialize sprint meter to max
	SprintMeter = SprintTime;

	// Initialize the walk speed
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	// start the sprint tick timer
	GetWorld()->GetTimerManager().SetTimer(SprintTimer, this, &ANPPlayerCharacter::SprintFixedTick, SprintFixedTickTime, true);

	// timer for interaction line detect
	GetWorldTimerManager().SetTimer(TimerHandle_Interaction, this, &ANPPlayerCharacter::PerformInteractionCheck, 0.1f, true);
}

void ANPPlayerCharacter::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// clear the sprint timer
	GetWorld()->GetTimerManager().ClearTimer(SprintTimer);
}


void ANPPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float CurrentZ = CameraBoom->GetRelativeLocation().Z;

	float StandingHalfHeight = GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
	float CrouchedHalfHeight = GetCharacterMovement()->GetCrouchedHalfHeight();
	float TotalAdjustment = StandingHalfHeight - CrouchedHalfHeight;

	float TargetZ = bIsCrouched ? (DefaultCameraLoc.Z - TotalAdjustment) : DefaultCameraLoc.Z;

	float NewZ = FMath::FInterpTo(CurrentZ, TargetZ, DeltaTime, 7.0f);
	CameraBoom->SetRelativeLocation(FVector(DefaultCameraLoc.X, DefaultCameraLoc.Y, NewZ));

	if (GetCharacterMovement()->IsFalling())
	{
		if (GetVelocity().Z < 0.8f)
		{
			GetCharacterMovement()->GravityScale = 1.9f;
		}
		else
		{
			GetCharacterMovement()->GravityScale = 1.0f;
		}
	}
	else
	{
		GetCharacterMovement()->GravityScale = 1.0f;
	}
}

void ANPPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	checkf(InputConfigDataAsset, TEXT("Forgot to assign a valid data asset as input config"));

	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	check(Subsystem);

	Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);

	UNPInputComponent* NPInputComponent = CastChecked<UNPInputComponent>(PlayerInputComponent);

	// Move & Look
	NPInputComponent->BindNativeInputAction(InputConfigDataAsset, NPGamplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::MoveInput);
	NPInputComponent->BindNativeInputAction(InputConfigDataAsset, NPGamplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::LookInput);

	// Jump
	NPInputComponent->BindNativeInputAction(InputConfigDataAsset, NPGamplayTags::InputTag_Jump, ETriggerEvent::Started, this, &ThisClass::DoJumpStart);
	NPInputComponent->BindNativeInputAction(InputConfigDataAsset, NPGamplayTags::InputTag_Jump, ETriggerEvent::Completed, this, &ThisClass::DoJumpEnd);

	// Crouch
	NPInputComponent->BindNativeInputAction(InputConfigDataAsset, NPGamplayTags::InputTag_Crouch, ETriggerEvent::Started, this, &ThisClass::DoCrouchStart);
	NPInputComponent->BindNativeInputAction(InputConfigDataAsset, NPGamplayTags::InputTag_Crouch, ETriggerEvent::Completed, this, &ThisClass::DoCrouchEnd);

	// Sprint
	NPInputComponent->BindNativeInputAction(InputConfigDataAsset, NPGamplayTags::InputTag_Sprint, ETriggerEvent::Started, this, &ThisClass::DoStartSprint);
	NPInputComponent->BindNativeInputAction(InputConfigDataAsset, NPGamplayTags::InputTag_Sprint, ETriggerEvent::Completed, this, &ThisClass::DoEndSprint);

	// Interact
	NPInputComponent->BindNativeInputAction(InputConfigDataAsset, NPGamplayTags::InputTag_Interact, ETriggerEvent::Started, this, &ThisClass::Interact);

	// Inventory
	NPInputComponent->BindNativeInputAction(InputConfigDataAsset, NPGamplayTags::InputTag_ItemListCall, ETriggerEvent::Started, this, &ThisClass::ItemListCall);

	// Narration Bar
	NPInputComponent->BindNativeInputAction(InputConfigDataAsset, NPGamplayTags::InputTag_NextSentence, ETriggerEvent::Started, this, &ThisClass::Next_Sentence);

	// Get Phone Call
	NPInputComponent->BindNativeInputAction(InputConfigDataAsset, NPGamplayTags::InputTag_PhoneCall, ETriggerEvent::Started, this, &ThisClass::Get_Phone);
}


void ANPPlayerCharacter::MoveInput(const FInputActionValue& Value)
{
	// get the Vector2D move axis
	FVector2D MovementVector = Value.Get<FVector2D>();

	// pass the axis values to the move input
	DoMove(MovementVector.X, MovementVector.Y);

}

void ANPPlayerCharacter::LookInput(const FInputActionValue& Value)
{
	// get the Vector2D look axis
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// pass the axis values to the aim input
	DoAim(LookAxisVector.X, LookAxisVector.Y);

}

void ANPPlayerCharacter::DoAim(float Yaw, float Pitch)
{
	if (GetController())
	{
		// pass the rotation inputs
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void ANPPlayerCharacter::DoMove(float Right, float Forward)
{
	if (GetController())
	{
		// pass the move inputs
		AddMovementInput(GetActorRightVector(), Right);
		AddMovementInput(GetActorForwardVector(), Forward);
	}
}

void ANPPlayerCharacter::DoJumpStart()
{
	// pass Jump to the character
	Jump();
}

void ANPPlayerCharacter::DoJumpEnd()
{
	// pass StopJumping to the character
	StopJumping();
}

void ANPPlayerCharacter::DoCrouchStart()
{
	if (GetCharacterMovement()->IsFalling())
	{
		bWantsToCrouchBuffer = true;
	}
	else
	{
		Crouch();
	}
}

void ANPPlayerCharacter::DoCrouchEnd()
{
	bWantsToCrouchBuffer = false;
	UnCrouch();
}

void ANPPlayerCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	if (bWantsToCrouchBuffer)
	{
		Crouch();
		bWantsToCrouchBuffer = false;
	}
}

void ANPPlayerCharacter::OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	Super::OnStartCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
	FVector NewLoc = CameraBoom->GetRelativeLocation();
	NewLoc.Z += ScaledHalfHeightAdjust;
	CameraBoom->SetRelativeLocation(NewLoc);
}

void ANPPlayerCharacter::OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	Super::OnEndCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
	FVector NewLoc = CameraBoom->GetRelativeLocation();
	NewLoc.Z -= ScaledHalfHeightAdjust;
	CameraBoom->SetRelativeLocation(NewLoc);
}

void ANPPlayerCharacter::DoStartSprint()
{

	if (GetCharacterMovement()->IsCrouching())
	{
		return;
	}

	// set the sprinting flag
	bSprinting = true;

	// are we out of recovery mode?
	if (!bRecovering)
	{
		// set the sprint walk speed
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;

		// call the sprint state changed delegate
		PlayerUIComponent->OnSprintStateChanged.Broadcast(true);
	}

}

void ANPPlayerCharacter::DoEndSprint()
{
	// set the sprinting flag
	bSprinting = false;

	// are we out of recovery mode?
	if (!bRecovering)
	{
		// set the default walk speed
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

		// call the sprint state changed delegate
		PlayerUIComponent->OnSprintStateChanged.Broadcast(false);
	}
}

void ANPPlayerCharacter::SprintFixedTick()
{
	if (bIsCrouched)
	{
		DoEndSprint();
	}
	// are we out of recovery, still have stamina and are moving faster than our walk speed?
	if (bSprinting && !bRecovering && GetVelocity().Length() > WalkSpeed)
	{

		// do we still have meter to burn?
		if (SprintMeter > 0.0f)
		{
			// update the sprint meter
			SprintMeter = FMath::Max(SprintMeter - SprintFixedTickTime, 0.0f);

			// have we run out of stamina?
			if (SprintMeter <= 0.0f)
			{
				// raise the recovering flag
				bRecovering = true;

				// set the recovering walk speed
				GetCharacterMovement()->MaxWalkSpeed = RecoveringWalkSpeed;
			}
		}

	}
	else {

		// recover stamina
		SprintMeter = FMath::Min(SprintMeter + SprintFixedTickTime, SprintTime);

		if (SprintMeter >= SprintTime)
		{
			// lower the recovering flag
			bRecovering = false;

			// set the walk or sprint speed depending on whether the sprint button is down
			GetCharacterMovement()->MaxWalkSpeed = bSprinting ? SprintSpeed : WalkSpeed;

			// update the sprint state depending on whether the button is down or not
			PlayerUIComponent->OnSprintStateChanged.Broadcast(bSprinting);
		}

	}

	// broadcast the sprint meter updated delegate
	PlayerUIComponent->OnSprintMeterUpdated.Broadcast(SprintMeter / SprintTime);

}

void ANPPlayerCharacter::Next_Sentence()
{
	NarrationComponent->SkipSub.Broadcast();

	Debug::Print(TEXT("Pressed Narration Button"));
}

void ANPPlayerCharacter::Get_Phone()
{
	NarrationComponent->CallApprove.Broadcast();

	Debug::Print(TEXT("Pressed Phone Button"));
}

void ANPPlayerCharacter::PerformInteractionCheck()
{
	// 1. 레이저의 시작점과 끝점 설정 (카메라 위치 기준)
	FVector EyesLocation;
	FRotator EyesRotation;
	GetActorEyesViewPoint(EyesLocation, EyesRotation);

	FVector TraceEnd = EyesLocation + (EyesRotation.Vector() * 500.f); // 5 meter

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this); // ignore self

	// 2. 라인트레이스 실행
	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult, EyesLocation, TraceEnd, ECC_Visibility, QueryParams);

	if (bHit)
	{
		AActor* HitActor = HitResult.GetActor();
		// 3. 맞은 액터가 인터페이스를 가지고 있는지 확인
		if (HitActor && HitActor->GetClass()->ImplementsInterface(UInteractInterface::StaticClass()))
		{
			if (TargetActor != HitActor)
			{
				TargetActor = HitActor;
			}
			return;
		}
	}

	if (TargetActor)
	{
		TargetActor = nullptr;
	}
}

void ANPPlayerCharacter::Interact()
{
	// 현재 타겟이 있고, 실제로 E키를 눌렀을 때만 발동
	if (TargetActor)
	{
		IInteractInterface::Execute_Interact(TargetActor, this);
		Debug::Print((TEXT("%s"), TargetActor->GetActorNameOrLabel()));
	}
}

UItemInventoryComponentBase* ANPPlayerCharacter::GetInventoryComponentDefualt() const
{
	return PlayerInventoryComponent;
}

UPawnUIComponent* ANPPlayerCharacter::GetPawnUIComponent() const
{
	return PlayerUIComponent;
}

UPlayerUIComponent* ANPPlayerCharacter::GetPlayerUIComponent() const
{
	return PlayerUIComponent;
}

void ANPPlayerCharacter::ItemListCall()
{
	float CurrentTime = GetWorld()->GetRealTimeSeconds();

	if (CurrentTime - LastUICallTime >= UICallCooldown)
	{
		LastUICallTime = CurrentTime;

		PlayerUIComponent->OnInventoryCalled.Broadcast();
	}
}

UNarrationalUIComponent* ANPPlayerCharacter::GetNarrationUIComponent() const
{
	return NarrationComponent;
}

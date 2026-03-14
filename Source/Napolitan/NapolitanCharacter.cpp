// Copyright Epic Games, Inc. All Rights Reserved.

#include "NapolitanCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Napolitan.h"

#include "DebugHelper.h"

ANapolitanCharacter::ANapolitanCharacter()
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

	// 간접 표시용 메시
	GetMesh()->SetOwnerNoSee(true);
	GetMesh()->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::WorldSpaceRepresentation;

	// Configure character movement
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	GetCharacterMovement()->AirControl = 0.5f;
	GetCharacterMovement()->MaxWalkSpeedCrouched = CrouchSpeed;
}

void ANapolitanCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float CurrentZ = CameraBoom->GetRelativeLocation().Z;

	float StandingHalfHeight = GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
	float CrouchedHalfHeight = GetCharacterMovement()->GetCrouchedHalfHeight();
	float TotalAdjustment = StandingHalfHeight - CrouchedHalfHeight;

	float TargetZ = bIsCrouched ? (DefaultCameraLoc.Z - TotalAdjustment) : DefaultCameraLoc.Z;

	float NewZ = FMath::FInterpTo(CurrentZ, TargetZ, DeltaTime, 7.0f);
	CameraBoom->SetRelativeLocation(FVector(DefaultCameraLoc.X, DefaultCameraLoc.Y, NewZ));
}

void ANapolitanCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ANapolitanCharacter::DoJumpStart);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ANapolitanCharacter::DoJumpEnd);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ANapolitanCharacter::MoveInput);

		// Looking/Aiming
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ANapolitanCharacter::LookInput);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &ANapolitanCharacter::LookInput);

		// Crawling
		EnhancedInputComponent->BindAction(Crawling, ETriggerEvent::Started, this, &ANapolitanCharacter::DoCrouchStart);
		EnhancedInputComponent->BindAction(Crawling, ETriggerEvent::Completed, this, &ANapolitanCharacter::DoCrouchEnd);
	}
	else
	{
		UE_LOG(LogNapolitan, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void ANapolitanCharacter::MoveInput(const FInputActionValue& Value)
{
	// get the Vector2D move axis
	FVector2D MovementVector = Value.Get<FVector2D>();

	// pass the axis values to the move input
	DoMove(MovementVector.X, MovementVector.Y);

}

void ANapolitanCharacter::LookInput(const FInputActionValue& Value)
{
	// get the Vector2D look axis
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// pass the axis values to the aim input
	DoAim(LookAxisVector.X, LookAxisVector.Y);

}

void ANapolitanCharacter::DoAim(float Yaw, float Pitch)
{
	if (GetController())
	{
		// pass the rotation inputs
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void ANapolitanCharacter::DoMove(float Right, float Forward)
{
	if (GetController())
	{
		// pass the move inputs
		AddMovementInput(GetActorRightVector(), Right);
		AddMovementInput(GetActorForwardVector(), Forward);
	}
}

void ANapolitanCharacter::DoJumpStart()
{
	// pass Jump to the character
	Jump();
}

void ANapolitanCharacter::DoJumpEnd()
{
	// pass StopJumping to the character
	StopJumping();
}

void ANapolitanCharacter::DoCrouchStart()
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

void ANapolitanCharacter::DoCrouchEnd()
{
	bWantsToCrouchBuffer = false;
	UnCrouch();
}

void ANapolitanCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	if (bWantsToCrouchBuffer)
	{
		Crouch();
		bWantsToCrouchBuffer = false;
	}
}

void ANapolitanCharacter::OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	Super::OnStartCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
	FVector NewLoc = CameraBoom->GetRelativeLocation();
	NewLoc.Z += ScaledHalfHeightAdjust;
	CameraBoom->SetRelativeLocation(NewLoc);
}

void ANapolitanCharacter::OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	Super::OnEndCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
	FVector NewLoc = CameraBoom->GetRelativeLocation();
	NewLoc.Z -= ScaledHalfHeightAdjust;
	CameraBoom->SetRelativeLocation(NewLoc);
}

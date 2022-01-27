//Copyright 2021, Dakota Dawe, All rights reserved

#include "Actors/FPSTemplateCharacter.h"
#include "Actors/FPSTemplateFirearm.h"
#include "Blueprint/UserWidget.h"
#include "Components/FPSTemplate_CharacterComponent.h"
#include "Components/FPS_CharacterMovementComponent.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

AFPSTemplateCharacter::AFPSTemplateCharacter(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer.SetDefaultSubobjectClass<UFPS_CharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	GetMesh()->bCastHiddenShadow = true;

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;
	
	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(GetCapsuleComponent());
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	CharacterComponent = CreateDefaultSubobject<UFPSTemplate_CharacterComponent>(TEXT("CharacterComponent"));
}

void AFPSTemplateCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

void AFPSTemplateCharacter::PostInitProperties()
{
	Super::PostInitProperties();
}

void AFPSTemplateCharacter::OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	Super::OnStartCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
	if (Mesh1P)
	{
		FVector CurrentLoc = Mesh1P->GetRelativeLocation();
		CurrentLoc.Z += HalfHeightAdjust;
		Mesh1P->SetRelativeLocation(CurrentLoc);
	}
}

void AFPSTemplateCharacter::OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	Super::OnEndCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
	if (Mesh1P)
	{
		FVector CurrentLoc = Mesh1P->GetRelativeLocation();
		CurrentLoc.Z -= HalfHeightAdjust;
		Mesh1P->SetRelativeLocation(CurrentLoc);
	}
}

void AFPSTemplateCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSTemplateCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSTemplateCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &AFPSTemplateCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("TurnRate", this, &AFPSTemplateCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &AFPSTemplateCharacter::LookUpAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AFPSTemplateCharacter::LookUpAtRate);
}

void AFPSTemplateCharacter::StartSprinting()
{
	if (UFPS_CharacterMovementComponent* FPSMovementComponent = Cast<UFPS_CharacterMovementComponent>(GetCharacterMovement()))
	{
		FPSMovementComponent->SetSprinting(true);
	}
}

void AFPSTemplateCharacter::StopSprinting()
{
	if (UFPS_CharacterMovementComponent* FPSMovementComponent = Cast<UFPS_CharacterMovementComponent>(GetCharacterMovement()))
	{
		FPSMovementComponent->SetSprinting(false);
	}
}

void AFPSTemplateCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AFPSTemplateCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AFPSTemplateCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	if (Rate != 0.0f)
	{
		Rate *= CharacterComponent->GetMagnificationSensitivity();
		AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
	}
}

void AFPSTemplateCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	if (Rate != 0.0f)
	{
		Rate *= CharacterComponent->GetMagnificationSensitivity();
		AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
	}
}
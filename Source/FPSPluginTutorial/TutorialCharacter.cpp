// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialCharacter.h"
#include "Components/FPS_CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ATutorialCharacter::ATutorialCharacter(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer.SetDefaultSubobjectClass<UFPS_CharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bFreeLooking = false;
}

// Called when the game starts or when spawned
void ATutorialCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATutorialCharacter::StartFreeLook(bool EnableFreeLook)
{
	bFreeLooking = EnableFreeLook;

	if (!bFreeLooking)
	{
		if (AController* MyController = GetController())
		{
			MyController->SetControlRotation(FreeLookControlRotation);
		}
	}
	FreeLookControlRotation = GetControlRotation();
	bUseControllerRotationYaw = !bFreeLooking;
}

bool ATutorialCharacter::ValidTurn(float AxisValue)
{
	if (bFreeLooking)
	{
		FRotator Delta = UKismetMathLibrary::NormalizedDeltaRotator(GetActorRotation(), GetControlRotation());
		float Limit = 35.0f;

		if (Delta.Yaw > Limit && AxisValue < 0.0f)
		{
			return false;
		}
		if (Delta.Yaw < -Limit && AxisValue > 0.0f)
		{
			return false;
		}
	}
	return true;
}

bool ATutorialCharacter::ValidUp(float AxisValue)
{
	if (bFreeLooking)
	{
		FRotator Delta = UKismetMathLibrary::NormalizedDeltaRotator(GetActorRotation(), GetControlRotation());
		float Limit = 35.0f;
		UE_LOG(LogTemp, Warning, TEXT("Delta: %f"), Delta.Pitch);

		if (Delta.Pitch > Limit && AxisValue > 0.0f)
		{
			return false;
		}
		if (Delta.Pitch < -Limit && AxisValue < 0.0f)
		{
			return false;
		}
	}
	return true;
}

// Called every frame
void ATutorialCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATutorialCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


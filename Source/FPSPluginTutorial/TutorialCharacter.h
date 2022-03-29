// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TutorialCharacter.generated.h"

UCLASS()
class FPSPLUGINTUTORIAL_API ATutorialCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATutorialCharacter(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool bFreeLooking;
	FRotator FreeLookControlRotation;
	
	UFUNCTION(BlueprintCallable, Category = "TUTORIAL")
	void StartFreeLook(bool EnableFreeLook);
	UFUNCTION(BlueprintCallable, Category = "TUTORIAL", meta = (ExpandBoolAsExecs = "ReturnValue"))
	bool ValidTurn(float AxisValue);
	UFUNCTION(BlueprintCallable, Category = "TUTORIAL", meta = (ExpandBoolAsExecs = "ReturnValue"))
	bool ValidUp(float AxisValue);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

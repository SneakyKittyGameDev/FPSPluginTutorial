//Copyright 2021, Dakota Dawe, All rights reserved
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSTemplateCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UFPSTemplate_CharacterComponent;

UCLASS()
class ULTIMATEFPSTEMPLATE_API AFPSTemplateCharacter : public ACharacter
{
	GENERATED_BODY()
protected:
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UFPSTemplate_CharacterComponent* CharacterComponent;

public:
	AFPSTemplateCharacter(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay();
	virtual void PostInitProperties() override;
	virtual void OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	virtual void OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:
	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Character")
	void StartSprinting();
	UFUNCTION(BlueprintCallable, Category = "FPSTemplate | Character")
	void StopSprinting();

	UFUNCTION(BlueprintCallable, Category = "Default Functions")
	void MoveForward(float Val);
	UFUNCTION(BlueprintCallable, Category = "Default Functions")
	void MoveRight(float Val);
	UFUNCTION(BlueprintCallable, Category = "Default Functions")
	void TurnAtRate(float Rate);
	UFUNCTION(BlueprintCallable, Category = "Default Functions")
	void LookUpAtRate(float Rate);
	
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	
public:	
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
};

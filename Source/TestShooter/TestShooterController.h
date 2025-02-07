// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TestShooterController.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class TESTSHOOTER_API ATestShooterController : public APlayerController
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* EquipNextInputAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* AttackInputAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* AimInputAction;


	UPROPERTY(EditDefaultsOnly)
	UInputAction* JogInputAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* CrouchInputAction;


public:

	void SetupInput(class UInputComponent* PlayerInputComponent);

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void OnAttackActionStarted(const FInputActionValue& Value);

	void OnAttackActionEnded(const FInputActionValue& Value);


	void OnEquipNextTriggered(const FInputActionValue& Value);

	void OnAimActionStarted(const FInputActionValue& Value);

	void OnAimActionEnded(const FInputActionValue& Value);


	void OnJogActionStarted(const FInputActionValue& Value);

	void OnJogActionEnded(const FInputActionValue& Value);

	void OnCrouchActionStarted(const FInputActionValue& Value);

	void OnCrouchActionEnded(const FInputActionValue& Value);



};

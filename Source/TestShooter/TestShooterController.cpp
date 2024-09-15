// Fill out your copyright notice in the Description page of Project Settings.


#include "TestShooterController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Inventory/NewInventoryComponent.h"
#include "TestShooterCharacter.h"


void ATestShooterController::SetupInput(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}


	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent)) {
		if (ACharacter* ControlledCharacter = Cast<ACharacter>(GetPawn()))
		{
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, ControlledCharacter, &ACharacter::Jump);

			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, ControlledCharacter, &ACharacter::StopJumping);
		}

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATestShooterController::Move);

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATestShooterController::Look);

		if (EquipNextInputAction)
		{
			EnhancedInputComponent->BindAction(EquipNextInputAction, ETriggerEvent::Triggered, this, &ATestShooterController::OnEquipNextTriggered);
		}

		if (AttackInputAction)
		{
			EnhancedInputComponent->BindAction(AttackInputAction, ETriggerEvent::Started, this, &ATestShooterController::OnAttackActionStarted);
			EnhancedInputComponent->BindAction(AttackInputAction, ETriggerEvent::Completed, this, &ATestShooterController::OnAttackActionEnded);
		}

		if (AimInputAction)
		{
			EnhancedInputComponent->BindAction(AimInputAction, ETriggerEvent::Started, this, &ATestShooterController::OnAimActionStarted);
			EnhancedInputComponent->BindAction(AimInputAction, ETriggerEvent::Completed, this, &ATestShooterController::OnAimActionEnded);
		}

		if (JogInputAction)
		{
			EnhancedInputComponent->BindAction(JogInputAction, ETriggerEvent::Started, this, &ATestShooterController::OnJogActionStarted);
			EnhancedInputComponent->BindAction(JogInputAction, ETriggerEvent::Completed, this, &ATestShooterController::OnJogActionEnded);
		}

		if (CrouchInputAction)
		{
			EnhancedInputComponent->BindAction(CrouchInputAction, ETriggerEvent::Started, this, &ATestShooterController::OnCrouchActionStarted);
			EnhancedInputComponent->BindAction(CrouchInputAction, ETriggerEvent::Completed, this, &ATestShooterController::OnCrouchActionEnded);
		}
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}	
}

void ATestShooterController::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	GetPawn()->AddMovementInput(ForwardDirection, MovementVector.Y);
	GetPawn()->AddMovementInput(RightDirection, MovementVector.X);

}

void ATestShooterController::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddYawInput(LookAxisVector.X);
	AddPitchInput(LookAxisVector.Y);

}

void ATestShooterController::OnEquipNextTriggered(const FInputActionValue& Value)
{
	FGameplayEventData EventPayload;
	EventPayload.EventTag = Cast<ATestShooterCharacter>(GetPawn())->EquipNextEventTag;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetPawn(), Cast<ATestShooterCharacter>(GetPawn())->EquipNextEventTag, EventPayload);
}

void ATestShooterController::OnAttackActionStarted(const FInputActionValue& Value)
{
	FGameplayEventData EventPayload;
	EventPayload.EventTag = Cast<ATestShooterCharacter>(GetPawn())->AttackStartedEventTag;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetPawn(), Cast<ATestShooterCharacter>(GetPawn())->AttackStartedEventTag, EventPayload);
}

void ATestShooterController::OnAttackActionEnded(const FInputActionValue& Value)
{
	FGameplayEventData EventPayload;
	EventPayload.EventTag = Cast<ATestShooterCharacter>(GetPawn())->AttackEndedEventTag;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetPawn(), Cast<ATestShooterCharacter>(GetPawn())->AttackEndedEventTag, EventPayload);
}


void ATestShooterController::OnAimActionStarted(const FInputActionValue& Value)
{
	FGameplayEventData EventPayload;
	EventPayload.EventTag = Cast<ATestShooterCharacter>(GetPawn())->AimStartedEventTag;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetPawn(), Cast<ATestShooterCharacter>(GetPawn())->AimStartedEventTag, EventPayload);
}

void ATestShooterController::OnAimActionEnded(const FInputActionValue& Value)
{
	FGameplayEventData EventPayload;
	EventPayload.EventTag = Cast<ATestShooterCharacter>(GetPawn())->AimEndedEventTag;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetPawn(), Cast<ATestShooterCharacter>(GetPawn())->AimEndedEventTag, EventPayload);
}

void ATestShooterController::OnJogActionStarted(const FInputActionValue& Value)
{
	FGameplayEventData EventPayload;
	EventPayload.EventTag = Cast<ATestShooterCharacter>(GetPawn())->JogStartedEventTag;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetPawn(), Cast<ATestShooterCharacter>(GetPawn())->JogStartedEventTag, EventPayload);
}

void ATestShooterController::OnJogActionEnded(const FInputActionValue& Value)
{
	FGameplayEventData EventPayload;
	EventPayload.EventTag = Cast<ATestShooterCharacter>(GetPawn())->JogEndedEventTag;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetPawn(), Cast<ATestShooterCharacter>(GetPawn())->JogEndedEventTag, EventPayload);
}

void ATestShooterController::OnCrouchActionStarted(const FInputActionValue& Value)
{
	FGameplayEventData EventPayload;
	EventPayload.EventTag = Cast<ATestShooterCharacter>(GetPawn())->CrouchStartedEventTag;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetPawn(), Cast<ATestShooterCharacter>(GetPawn())->CrouchStartedEventTag, EventPayload);
}

void ATestShooterController::OnCrouchActionEnded(const FInputActionValue& Value)
{
	FGameplayEventData EventPayload;
	EventPayload.EventTag = Cast<ATestShooterCharacter>(GetPawn())->CrouchEndedEventTag;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetPawn(), Cast<ATestShooterCharacter>(GetPawn())->CrouchEndedEventTag, EventPayload);
}

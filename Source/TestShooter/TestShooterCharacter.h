// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "AbilitySystemInterface.h"
#include "TestShooterTypes.h"
#include "Abilities/GameplayAbility.h"
#include "TestShooterCharacter.generated.h"

struct FGameplayEffectContextHandle;
class UAbilitySystemComponentBase;
class UAttributeSetBase;
class UGameplayEffect;
class USpringArmComponent;
class UCameraComponent;
class UNewInventoryComponent;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ATestShooterCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;


public:
	ATestShooterCharacter();

	bool ApplyGameplayEffectToSelf(TSubclassOf<UGameplayEffect> Effect, FGameplayEffectContextHandle Context);

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;


protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void GiveAbilities();
	void ApplyStartupEffects();

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	UFUNCTION()
	void OnRep_CharacterData();

	virtual void InitFromFCharacterData(const FMyCharacterData& InCharacterData, bool bFromReplication = false);


public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	virtual void PostInitializeComponents() override;

	UFUNCTION(BlueprintCallable)
	FMyCharacterData GetCharacterData() const;

	UFUNCTION(BlueprintCallable)
	void SetCharacterData(const FMyCharacterData& InCharacterData);

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

protected:
	UPROPERTY(EditDefaultsOnly)
	UAbilitySystemComponentBase* AbilitySystemComponent;

	UPROPERTY(Transient)
	UAttributeSetBase* AttributeSet;

	UPROPERTY(EditDefaultsOnly)
	class UCharacterDataAsset* CharacterDataAsset;

	UPROPERTY(ReplicatedUsing = OnRep_CharacterData)
	FMyCharacterData CharacterData;

	//UPROPERTY(EditAnywhere, Replicated)
	//UNewInventoryComponent* InventoryComponent = nullptr;

public:
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag AttackStartedEventTag;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag AttackEndedEventTag;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag AimStartedEventTag;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag AimEndedEventTag;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag ZeroHealthEventTag;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag JogStartedEventTag;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag JogEndedEventTag;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag CrouchStartedEventTag;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag CrouchEndedEventTag;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag EquipNextEventTag;


	UPROPERTY(EditAnywhere, Replicated, BlueprintReadOnly)
	UNewInventoryComponent* NewInventoryComponent = nullptr;

};


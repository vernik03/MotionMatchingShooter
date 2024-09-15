// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Abilities/TestShooterGameplayAbility.h"
#include "Inventory/ItemActors/WeaponActor.h"
#include "GA_InventoryAbility.generated.h"

class UNewInventoryComponent;
class UInventoryItemInstance;
class UWeaponStaticData;
class AItemActor;

UCLASS()
class TESTSHOOTER_API UGA_InventoryAbility : public UTestShooterGameplayAbility
{
	GENERATED_BODY()

public:

	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	UFUNCTION(BlueprintPure)
	UNewInventoryComponent* GetInventoryComponent() const;

	UFUNCTION(BlueprintPure)
	UInventoryItemInstance* GetEquippedItemInstance() const;

	UFUNCTION(BlueprintPure)
	const UItemsStaticData* GetEquippedItemStaticData() const;

	UFUNCTION(BlueprintPure)
	const UWeaponStaticData* GetEquippedItemWeaponStaticData() const;

	UFUNCTION(BlueprintPure)
	AItemActor* GetEquippedItemActor() const;

	UFUNCTION(BlueprintPure)
	AWeaponActor* GetEquippedWeaponItemActor() const;

	UFUNCTION(BlueprintPure)
	FGameplayEffectSpecHandle GetWeaponEffectSpec(const FHitResult& InHitResult);

protected:

	UPROPERTY()
	UNewInventoryComponent* InventoryComponent = nullptr;

	
};

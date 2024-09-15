// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/GA_InventoryAbility.h"

#include "Inventory/NewInventoryComponent.h"

#include "Inventory/InventoryItemInstance.h"
#include "TestShooterTypes.h"
#include "Actors/ItemActor.h"
#include "Inventory/ItemActors/WeaponActor.h"

void UGA_InventoryAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	InventoryComponent = ActorInfo->OwnerActor.Get()->FindComponentByClass<UNewInventoryComponent>();
}

UNewInventoryComponent* UGA_InventoryAbility::GetInventoryComponent() const
{
	return InventoryComponent;
}

UInventoryItemInstance* UGA_InventoryAbility::GetEquippedItemInstance() const
{
	return InventoryComponent ? InventoryComponent->GetEquippedItem() : nullptr;
}

const UItemsStaticData* UGA_InventoryAbility::GetEquippedItemStaticData() const
{
	UInventoryItemInstance* EquippedItem = GetEquippedItemInstance();

	return EquippedItem ? EquippedItem->GetItemStaticData() : nullptr;
}

const UWeaponStaticData* UGA_InventoryAbility::GetEquippedItemWeaponStaticData() const
{
	return Cast<UWeaponStaticData>(GetEquippedItemStaticData());
}

AItemActor* UGA_InventoryAbility::GetEquippedItemActor() const
{
	UInventoryItemInstance* EquippedItem = GetEquippedItemInstance();

	return EquippedItem ? EquippedItem->GetItemActor() : nullptr;
}

AWeaponActor* UGA_InventoryAbility::GetEquippedWeaponItemActor() const
{
	return Cast<AWeaponActor>(GetEquippedItemActor());
}



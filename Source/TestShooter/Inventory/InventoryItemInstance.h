// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestShooterTypes.h"
#include "UObject/NoExportTypes.h"
#include "Actors/ItemActor.h"
#include "InventoryItemInstance.generated.h"

/**
 * 
 */
UCLASS()
class TESTSHOOTER_API UInventoryItemInstance : public UObject
{
	GENERATED_BODY()


public:
	virtual bool IsSupportedForNetworking() const override
	{
		return true;
	}

	UFUNCTION(BlueprintCallable, BlueprintPure)
	const UItemsStaticData* GetItemStaticData() const;

	UPROPERTY(Replicated)
	TSubclassOf<UItemsStaticData> ItemStaticDataClass;

	UPROPERTY(ReplicatedUsing = OnRep_Equipped)
	bool bEquipped = false;

	UFUNCTION()
	void OnRep_Equipped();

	virtual void OnEquipped(AActor* InOwner = nullptr);
	virtual void OnUnEquipped(AActor* InOwner = nullptr);

	virtual void Init(TSubclassOf<UItemsStaticData> INItemStaticDataClass, int32 InQuantity);

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	UFUNCTION(BlueprintPure)
	AItemActor* GetItemActor() const;

	int32 GetQuantity() const { return Quantity; }

	void AddItems(int32 Count);

protected:
	UPROPERTY(Replicated)
	AItemActor* ItemActor = nullptr;

	UPROPERTY(Replicated)
	int32 Quantity = 1;

	void TryGrantAbilities(AActor* InOwner);

	void TryRemoveAbilities(AActor* InOwner);

	void TryApplyEffects(AActor* InOwner);

	void TryRemoveEffects(AActor* InOwner);

	UPROPERTY()
	TArray<FGameplayAbilitySpecHandle> GrantedAbilityHandles;

	TArray<FActiveGameplayEffectHandle> OngoingEffectHandles;

};

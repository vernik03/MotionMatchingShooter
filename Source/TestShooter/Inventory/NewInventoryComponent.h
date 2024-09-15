// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory/InventoryList.h"
#include "Abilities/GameplayAbilityTypes.h"
//#include "FastArrayTagCounter.h"
#include "NewInventoryComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TESTSHOOTER_API UNewInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UNewInventoryComponent();

	virtual void InitializeComponent() override;

	virtual bool ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags) override;

	UFUNCTION(BlueprintCallable)
	void AddItem(TSubclassOf<UItemsStaticData> InItemStaticDataClass);


	UFUNCTION(BlueprintCallable)
	void RemoveItem(TSubclassOf<UItemsStaticData> InItemStaticDataClass);

	UFUNCTION(BlueprintCallable)
	void EquipItem(TSubclassOf<UItemsStaticData> InItemStaticDataClass);

	UFUNCTION(BlueprintCallable)
	void EquipItemInstance(UInventoryItemInstance* InItemInstance);

	UFUNCTION(BlueprintCallable)
	void UnequipItem();

	UFUNCTION(BlueprintCallable)
	void EquipNext();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UInventoryItemInstance* GetEquippedItem() const;


	static FGameplayTag EquipItemActorTag;
	static FGameplayTag EquipNextTag;

protected:


	UPROPERTY(Replicated)
	FInventoryList InventoryList;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UItemsStaticData>> DefaultItems;

	UPROPERTY(Replicated)
	UInventoryItemInstance* CurrentItem = nullptr;

	UFUNCTION(Server, Reliable)
	void ServerHandleGameplayEvent(FGameplayEventData Payload);

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};

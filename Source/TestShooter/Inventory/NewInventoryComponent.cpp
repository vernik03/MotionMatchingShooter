// Fill out your copyright notice in the Description page of Project Settings.

#include "NewInventoryComponent.h"
#include "Engine/ActorChannel.h"
#include "Components/ActorComponent.h"
#include "Net/UnrealNetwork.h"


FGameplayTag UNewInventoryComponent::EquipItemActorTag;
FGameplayTag UNewInventoryComponent::DropItemTag;
FGameplayTag UNewInventoryComponent::EquipNextTag;
FGameplayTag UNewInventoryComponent::UnequipTag;

static TAutoConsoleVariable<int32> CVarShowInventory(
	TEXT("CVarShowInventory"),
	0,
	TEXT("Enables fast inventory replication"),
	ECVF_Default);


UNewInventoryComponent::UNewInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;
	SetIsReplicatedByDefault(true);

}

void UNewInventoryComponent::InitializeComponent()
{
	Super::InitializeComponent();

	if (GetOwner()->HasAuthority())
	{
		for (auto& ItemClass : DefaultItems)
		{
			InventoryList.AddItem(ItemClass);
		}

		if (InventoryList.GetItemsRef().Num())
		{
			EquipItem(InventoryList.GetItemsRef()[0].ItemInstance->ItemStaticDataClass);
		}
	}
}

bool UNewInventoryComponent::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool TestSubobject = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	for (FInventoryListItem& Item : InventoryList.GetItemsRef())
	{
		UInventoryItemInstance* ItemInstance = Item.ItemInstance;

		if (IsValid(ItemInstance))
		{
			TestSubobject |= Channel->ReplicateSubobject(ItemInstance, *Bunch, *RepFlags);
		}

	}

	return TestSubobject;
}

void UNewInventoryComponent::AddItem(TSubclassOf<UItemsStaticData> InItemStaticDataClass)
{
	InventoryList.AddItem(InItemStaticDataClass);
}

void UNewInventoryComponent::RemoveItem(TSubclassOf<UItemsStaticData> InItemStaticDataClass)
{
	InventoryList.RemoveItem(InItemStaticDataClass);
}

void UNewInventoryComponent::EquipItem(TSubclassOf<UItemsStaticData> InItemStaticDataClass)
{
	if (GetOwner()->HasAuthority())
	{
		for (auto Item : InventoryList.GetItemsRef())
		{
			if (Item.ItemInstance->ItemStaticDataClass == InItemStaticDataClass)
			{
				Item.ItemInstance->OnEquipped(GetOwner());

				CurrentItem = Item.ItemInstance;

				break;
			}
		}
	}
}

void UNewInventoryComponent::EquipItemInstance(UInventoryItemInstance* InItemInstance)
{
	if (GetOwner()->HasAuthority())
	{
		for (auto Item : InventoryList.GetItemsRef())
		{
			if (Item.ItemInstance == InItemInstance)
			{
				Item.ItemInstance->OnEquipped(GetOwner());
				CurrentItem = Item.ItemInstance;
				break;
			}
		}
	}
}

void UNewInventoryComponent::UnequipItem()
{
	if (GetOwner()->HasAuthority())
	{
		if (IsValid(CurrentItem))
		{
			CurrentItem->OnUnEquipped(GetOwner());
			CurrentItem = nullptr;
		}
	}
}

void UNewInventoryComponent::EquipNext()
{
	TArray<FInventoryListItem>& Items = InventoryList.GetItemsRef();

	const bool bNoItems = Items.Num() == 0;
	const bool bOneAndEquipped = Items.Num() == 1 && CurrentItem;

	if (bNoItems || bOneAndEquipped) return;

	UInventoryItemInstance* TargetItem = CurrentItem;

	for (auto Item : Items)
	{
		if (Item.ItemInstance->GetItemStaticData()->bCanBeEquipped)
		{
			if (Item.ItemInstance != CurrentItem)
			{
				TargetItem = Item.ItemInstance;
				break;
			}
		}
	}

	if (CurrentItem)
	{
		if (TargetItem == CurrentItem)
		{
			return;
		}

		UnequipItem();
	}

	EquipItemInstance(TargetItem);
}

UInventoryItemInstance* UNewInventoryComponent::GetEquippedItem() const
{
	return CurrentItem;
}


void UNewInventoryComponent::ServerHandleGameplayEvent_Implementation(FGameplayEventData Payload)
{

}

// Called every frame
void UNewInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const bool bShowDebug = CVarShowInventory.GetValueOnGameThread() != 0;
	if (bShowDebug)
	{
		for (FInventoryListItem& Item : InventoryList.GetItemsRef())
		{
			UInventoryItemInstance* ItemInstance = Item.ItemInstance;
			const UItemsStaticData* ItemStaticData = ItemInstance->GetItemStaticData();

			if (IsValid(ItemInstance) && IsValid(ItemStaticData))
			{
				GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Blue, FString::Printf(TEXT("Item: %s"), *ItemStaticData->Name.ToString()));
			}

		}

	}


}

void UNewInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UNewInventoryComponent, InventoryList);
	DOREPLIFETIME(UNewInventoryComponent, CurrentItem);

}


// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/InventoryItemInstance.h"
#include "Actors/ItemActor.h"
#include "TestShooterStatics.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"




void UInventoryItemInstance::Init(TSubclassOf<UItemsStaticData> INItemStaticDataClass)
{	
	ItemStaticDataClass = INItemStaticDataClass;
}

const UItemsStaticData* UInventoryItemInstance::GetItemStaticData() const
{
	return UTestShooterStatics::GetItemStaticData(ItemStaticDataClass);
}

void UInventoryItemInstance::OnRep_Equipped()
{
	
}

void UInventoryItemInstance::OnEquipped(AActor* InOwner)
{
	if (UWorld* World = InOwner->GetWorld())
	{
		const UItemsStaticData* ItemStaticData = GetItemStaticData();

		FTransform SpawnTransform;
		ItemActor = World->SpawnActorDeferred<AItemActor>(GetItemStaticData()->ItemActorClass, SpawnTransform, InOwner);
		ItemActor->Init(this);

		ItemActor->FinishSpawning(SpawnTransform);

		ACharacter* Character = Cast<ACharacter>(InOwner);
		if (USkeletalMeshComponent* MeshComponent = Character ? Character->GetMesh() : nullptr)
		{
			
			ItemActor->AttachToComponent(MeshComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, ItemStaticData->
			AttachSocketName);
		}

		
	}
}

void UInventoryItemInstance::OnUnEquipped(AActor* InOwner)
{
	if (ItemActor)
	{
		ItemActor->Destroy();
		ItemActor = nullptr;
	}

	//TryRemoveAbilities(InOwner);

	//TryRemoveEffects(InOwner);

	bEquipped = false;
}

void UInventoryItemInstance::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UInventoryItemInstance, ItemStaticDataClass);
	DOREPLIFETIME(UInventoryItemInstance, bEquipped);
	DOREPLIFETIME(UInventoryItemInstance, ItemActor);

}


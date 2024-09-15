// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/GameplayEventNotify.h"

#include "AbilitySystemBlueprintLibrary.h"


void UGameplayEventNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(MeshComp->GetOwner(), Payload.EventTag, Payload);
}

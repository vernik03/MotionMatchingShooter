// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/ItemActor.h"
#include "WeaponActor.generated.h"

/**
 * 
 */
UCLASS()
class TESTSHOOTER_API AWeaponActor : public AItemActor
{
	GENERATED_BODY()

public:

	AWeaponActor();

	UFUNCTION(BlueprintCallable)
	const UWeaponStaticData* GetWeaponStaticData() const;

	UFUNCTION(BlueprintPure)
	FVector GetMuzzleLocation() const;

	UFUNCTION(BlueprintCallable)
	void PlayWeaponEffects(const FHitResult& InHitResult);

protected:

	UFUNCTION(NetMulticast, Reliable)
	void MulticastPlayWeaponEffects(const FHitResult& InHitResult);

	void PlayWeaponEffectsInternal(const FHitResult& InHitResult);

	UFUNCTION(BlueprintImplementableEvent)
	void PlayWeaponEffectsInBP(const FHitResult& InHitResult);


	UPROPERTY(BlueprintReadWrite)
	UMeshComponent* MeshComponent = nullptr;

	virtual void InitInternal() override;
	
};

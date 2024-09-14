// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TestShooterTypes.h"
#include "TestShooterStatics.generated.h"
/**
 * 
 */
UCLASS()
class TESTSHOOTER_API UTestShooterStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	
public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static const UItemsStaticData* GetItemStaticData(TSubclassOf<UItemsStaticData> ItemDataClass);
	
};



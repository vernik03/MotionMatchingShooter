// Fill out your copyright notice in the Description page of Project Settings.


#include "TestShooterStatics.h"

const UItemsStaticData* UTestShooterStatics::GetItemStaticData(TSubclassOf<UItemsStaticData> ItemDataClass)
{
	if (IsValid(ItemDataClass))
	{
		return GetDefault<UItemsStaticData>(ItemDataClass);
	}
	return nullptr;
}

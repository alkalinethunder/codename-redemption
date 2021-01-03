// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AssetUtils.generated.h"

/**
 * C++/Blueprint function library for dealing with assets.
 */
UCLASS(BlueprintType)
class REDEMPTION_API UAssetUtils : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Redemption|Assets")
	static TArray<UObject*> LoadAssetsOfClass(UClass* InClass);
};

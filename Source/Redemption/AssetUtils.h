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

public:
	template<typename T>
	static void LoadAssets(TArray<T*>& OutAssetArray);
};

template <typename T>
void UAssetUtils::LoadAssets(TArray<T*>& OutAssetArray)
{
	// clear the target array first
	OutAssetArray.Empty();

	// then just use the non-template LoadAssetsByClass() to get assets from Unreal
	for (UObject* obj : UAssetUtils::LoadAssetsOfClass(T::StaticClass()))
	{
		// Cast the asset reference
		T* asset = Cast<T>(obj);

		// If it's valid then we'll add it
		if (asset)
		{
			OutAssetArray.Add(asset);
		}
	}
}

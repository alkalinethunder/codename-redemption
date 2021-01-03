// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetUtils.h"
#include "AssetRegistry/AssetRegistryModule.h"

TArray<UObject*> UAssetUtils::LoadAssetsOfClass(UClass* InClass)
{
	FName name = InClass->GetFName();
	TArray<UObject*> result;
	
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	TArray<FAssetData> AssetData;
	AssetRegistryModule.Get().GetAssetsByClass(InClass->GetFName(), AssetData);

	for (FAssetData& Asset : AssetData)
	{
		result.Add(Asset.GetAsset());
	}

	return result;
}

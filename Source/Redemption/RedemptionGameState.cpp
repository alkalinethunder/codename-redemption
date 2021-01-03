// Fill out your copyright notice in the Description page of Project Settings.


#include "RedemptionGameState.h"
#include "UpgradeAsset.h"
#include "Math/Axis.h"
#include "AssetUtils.h"

// Sets default values
ARedemptionGameState::ARedemptionGameState()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARedemptionGameState::BeginPlay()
{
	Super::BeginPlay();
	
	for (UObject* asset : UAssetUtils::LoadAssetsOfClass(UUpgradeAsset::StaticClass()))
	{
		UUpgradeAsset* upgrade = Cast<UUpgradeAsset>(asset);
		if (upgrade)
		{
			this->Upgrades.Add(upgrade);
		}
	}
}

// Called every frame
void ARedemptionGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

TArray<UUpgradeAsset*> ARedemptionGameState::GetAllUpgrades()
{
	return this->Upgrades;
}


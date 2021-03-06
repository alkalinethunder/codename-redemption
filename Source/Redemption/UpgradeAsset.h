﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UpgradeCategory.h"
#include "UpgradeAsset.generated.h"

/**
 * Contains information about a single player upgrade.
 */
UCLASS(BlueprintType, Blueprintable)
class REDEMPTION_API UUpgradeAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Metadata")
	FText Name;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Metadata")
	FText Description;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Metadata")
	EUpgradeCategory Category;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Progression")
	TArray<UUpgradeAsset*> RequiredUpgrades;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Progression")
	int RequiredUpgradePoints = 1;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Progression")
	int RequiredSkillLevel = 1;

public:
	UFUNCTION(BlueprintPure, Category = "Upgrade")
	bool IsUnlocked(class ARedemptionPlayerState* InPlayerState);

	UFUNCTION(BlueprintPure, Category = "Upgrade")
	bool IsAvailable(class ARedemptionPlayerState* InPlayerState);

	UFUNCTION(BlueprintCallable, Category = "Upgrade")
	bool TryUnlock(class ARedemptionPlayerState* InPlayerState);
};

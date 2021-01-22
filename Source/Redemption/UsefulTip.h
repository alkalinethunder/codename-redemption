// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UpgradeAsset.h"
#include "UsefulTip.generated.h"

class ARedemptionPlayerController;

/**
 * 
 */
UCLASS(BlueprintType)
class REDEMPTION_API UUsefulTip : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Useful Tip")
	FText TipText;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Progression")
	UUpgradeAsset* RequiredUpgrade = nullptr;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Progression")
	FText TipTextAfterUpgrade;
	
public:
	UFUNCTION(BlueprintPure)
	FText GetTipText(ARedemptionPlayerController* InPlayerController);
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "DeviceType.h"
#include "Engine/DataAsset.h"
#include "HackableType.h"
#include "Difficulty.h"
#include "HackableAsset.generated.h"

UCLASS(BlueprintType)
class REDEMPTION_API UHackableAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Metadata")
	FText Name;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Metadata")
	FText Description;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Hackable")
	TArray<EDeviceType> SupportedDeviceTypes;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Hackable")
	EHackableType Type;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Hackable")
	EDifficulty Difficulty;
};

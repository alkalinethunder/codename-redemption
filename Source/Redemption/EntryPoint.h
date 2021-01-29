// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpawnFlags.h"
#include "UpgradeAsset.h"
#include "Engine/DataAsset.h"
#include "EntryPoint.generated.h"

UCLASS(BlueprintType)
class REDEMPTION_API UEntryPoint : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Metadata")
	FString CommandLineName;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Metadata")
	FText FullName;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Metadata")
	FText Description;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Metadata")
	FSpawnFlags SpawnFlags;
};

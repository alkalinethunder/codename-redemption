// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UpgradeAsset.h"
#include "CommandFlags.h"
#include "CommandScript.h"
#include "ShellCommandAsset.generated.h"

/**
 * Contains metadata for a Shell Command. Reuired for a Shell Command to be runnable
 * in-game by the player.
 */
UCLASS(BlueprintType)
class REDEMPTION_API UShellCommandAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Metadata")
	FString Name;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Metadata")
	FText HelpText;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Progression")
	UUpgradeAsset* RequiredUpgrade;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Flags")
	FCommandFlags CommandFlags;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Script")
	TSubclassOf<UCommandScript> CommandScriptClass;
};

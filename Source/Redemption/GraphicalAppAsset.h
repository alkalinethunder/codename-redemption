// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DisplayTarget.h"
#include "Blueprint/UserWidget.h"
#include "CommandFlags.h"
#include "UpgradeAsset.h"
#include "GraphicalAppAsset.generated.h"

class UAppWidget;

/**
 * Information about a graphical Operating System app.
 */
UCLASS(Blueprintable, BlueprintType)
class REDEMPTION_API UGraphicalAppAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Metadata")
	FString CommandName;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Metadata")
	FText Title;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Metadata")
	FText Description;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Display")
	UTexture2D* Icon;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Display")
	EDisplayTarget DisplayTarget;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Display")
	TSubclassOf<UAppWidget> WidgetClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Flags")
	FCommandFlags CommandFlags;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Progression")
	UUpgradeAsset* RequiredUpgrade = nullptr;
};

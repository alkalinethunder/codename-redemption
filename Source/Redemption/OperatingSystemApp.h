// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AppTabWidget.h"
#include "UObject/Object.h"
#include "GraphicalAppAsset.h"
#include "OperatingSystemApp.generated.h"

/**
 * Contains the GUI data of a graphical app.
 */
UCLASS(BlueprintType)
class REDEMPTION_API UOperatingSystemApp : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "App")
	UGraphicalAppAsset* AppAsset;
	
	UPROPERTY(BlueprintReadOnly, Category = "App")
	UAppWidget* AppWidget;

	UPROPERTY(BlueprintReadOnly, Category = "App")
	UAppTabWidget* TabWidget;
};

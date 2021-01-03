// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UpgradeCategory.generated.h"

/**
 * Represents a Code Shop upgrade category.
 */
UENUM(BlueprintType)
enum class EUpgradeCategory : uint8
{
    Desktop,
	HackingTools,
	Shell,
	SystemPerformance
};

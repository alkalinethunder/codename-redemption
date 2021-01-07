// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DisplayTarget.generated.h"

/**
 * Represents the target launch area of an Operating System app.
 */
UENUM(BlueprintType)
enum class EDisplayTarget : uint8
{
    Default,
	Social,
	InfoWidgets,
	SystemPanel,
	Floating
};

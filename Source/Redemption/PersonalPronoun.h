// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PersonalPronoun.generated.h"

/**
 * Represents a person's pronoun preference.
 */
UENUM(BlueprintType)
enum class EPersonalPronoun : uint8
{
    Male,
	Female,
	NonBinary
};

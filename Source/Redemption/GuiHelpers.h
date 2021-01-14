// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GuiHelpers.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class REDEMPTION_API UGuiHelpers : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "GUI utils for the Shell")
	static FText GetTimeFromNow(const FDateTime& InUtcDateTime);
};

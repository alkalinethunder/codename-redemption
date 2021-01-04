// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ConsoleTextData.generated.h"

/**
 * Contains a draw item for the in-game console.
 */
USTRUCT(BlueprintType)
struct FConsoleTextData
{
    GENERATED_BODY()

public:
	UPROPERTY()
	FString Text;

	UPROPERTY()
	FLinearColor Background;

	UPROPERTY()
	FLinearColor Foreground;

	UPROPERTY()
	FVector2D Location;

	UPROPERTY()
	FVector2D Size;
};

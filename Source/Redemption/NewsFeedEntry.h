// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NewsFeedEntry.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct REDEMPTION_API FNewsFeedEntry
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FString Text;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FString Sender;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FDateTime PostedOn;
};

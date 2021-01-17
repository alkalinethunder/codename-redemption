// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChatFlags.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FChatFlags
{
    GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool bMakeUnavailableOnCompletion = true;
};

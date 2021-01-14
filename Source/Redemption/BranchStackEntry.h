// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BranchStackEntry.generated.h"

/**
 * 
 */
USTRUCT()
struct REDEMPTION_API FBranchStackEntry
{
    GENERATED_BODY()

public:
	UPROPERTY()
	FName BranchId;
	
	UPROPERTY()
	int BranchPosition = 0;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DirectoryEntry.generated.h"

/**
 * Stores save file data for a directory in the in-game file system.
 */
USTRUCT(BlueprintType)
struct REDEMPTION_API FDirectoryEntry
{
   GENERATED_BODY()
	
public:
	UPROPERTY()
	int Id;

	UPROPERTY()
	FString Name;

	UPROPERTY()
	TArray<int> Children;

	UPROPERTY()
	TArray<int> Files;
};

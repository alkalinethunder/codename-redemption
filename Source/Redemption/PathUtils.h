// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PathUtils.generated.h"

/**
 * Static utils for dealing with in-game paths.
 */
UCLASS(BlueprintType)
class REDEMPTION_API UPathUtils : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure)
	static FString GetPathSeparatorString()
	{
		return "/";
	}

	UFUNCTION(BlueprintPure)
	static FString GetHomeDelimeterString()
	{
		return "~";
	}

	UFUNCTION(BlueprintPure)
	static FString GetThisDirectoryString()
	{
		return ".";
	}

	UFUNCTION(BlueprintPure)
    static FString GetUpOneDirectoryString()
	{
		return "..";
	}

public:
	UFUNCTION()
	static void GetPathParts(FString InPath, TArray<FString>& OutParts);
	
	UFUNCTION(BlueprintPure)
	static FString GetAbsolutePath(FString InWorkingDirectory, FString InRelativePath);
};

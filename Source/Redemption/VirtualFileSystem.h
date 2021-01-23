﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DiskNode.h"
#include "FileData.h"
#include "VirtualFileSystem.generated.h"

class URedemptionSaveGame;
class UDirectoryNode;
class UFileNode;

/**
 * 
 */
UCLASS()
class REDEMPTION_API UVirtualFileSystem : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY()
	FFileData Invalid;
	
	UPROPERTY()
	URedemptionSaveGame* SaveGame;
	
	UPROPERTY()
	UDiskNode* RootDiskNode;

private:
	UFUNCTION()
	UDiskNode* MapToNode(FString InPath);

	UFUNCTION()
	bool ResolveDirectory(FString InPath, UDirectoryNode*& OutNode);

	UFUNCTION()
    bool ResolveFile(FString InPath, UFileNode*& OutNode);
	
public:
	UFUNCTION()
	void MountRootNode(URedemptionSaveGame* InSaveGame, int InMountId);

public:
	UFUNCTION(BlueprintCallable)
	bool MakeDirectory(FString InPath);

	UFUNCTION(BlueprintPure)
	bool GetChildDirectoryPaths(FString InPath, TArray<FString>& OutChildren);

	UFUNCTION(BlueprintPure)
	bool GetChildFilePaths(FString InPath, TArray<FString>& OutChildren);
	
	UFUNCTION(BlueprintPure)
	bool DirectoryExists(FString InPath);

	UFUNCTION(BlueprintPure)
    bool FileExists(FString InPath);

	UFUNCTION(BlueprintPure)
	bool GetFileTextIfFileExists(FString InPath, FString& OutText);

	UFUNCTION()
	FString GetFileText(FString InPath);
	
	UFUNCTION()
	FFileData& GetFileData(FString InPath);
};

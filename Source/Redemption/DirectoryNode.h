// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DiskNode.h"
#include "FileType.h"
#include "DirectoryNode.generated.h"

class URedemptionSaveGame;
class UFileNode;

/**
 * Disk node that maps to a directory. 
 */
UCLASS()
class REDEMPTION_API UDirectoryNode : public UDiskNode
{
	GENERATED_BODY()

private:
	UPROPERTY()
	URedemptionSaveGame* SaveGame;

	UPROPERTY()
	int DirectoryId;

	UPROPERTY()
	TArray<UDiskNode*> Children;

	UPROPERTY()
	UDiskNode* Parent;

	UPROPERTY()
	bool ChildrenDirty = true;
	
public:
	virtual UDiskNode* GetParent() override;
	virtual FString GetDiskNodeName() override;
	virtual TArray<UDiskNode*> GetChildNodes() override;

public:
	UFUNCTION()
	void LinkToDirectory(UDiskNode* InParent, URedemptionSaveGame* InSaveGame, int InDirectoryId);

	UFUNCTION()
	UDirectoryNode* MakeChildDirectory(FString InName);

	UFUNCTION()
	TArray<UDirectoryNode*> GetChildDirectories();

	UFUNCTION()
	TArray<UFileNode*> GetChildFiles();

	UFUNCTION()
	UFileNode* CreateFile(FString InFileName, EFileType InFileType);
};

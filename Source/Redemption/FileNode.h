// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DiskNode.h"
#include "FileData.h"
#include "FileNode.generated.h"

class UDirectoryNode;
class URedemptionSaveGame;

/**
 * 
 */
UCLASS()
class REDEMPTION_API UFileNode : public UDiskNode
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UDirectoryNode* ParentNode;

	UPROPERTY()
	int FileId;

	UPROPERTY()
	URedemptionSaveGame* SaveGame;
	
public:
	virtual FString GetDiskNodeName() override;
	virtual TArray<UDiskNode*> GetChildNodes() override;
	virtual UDiskNode* GetParent() override;
	
public:
	UFUNCTION()
	void LinkToFile(UDirectoryNode* InParent, URedemptionSaveGame* InSaveGame, int InFileId);

	UFUNCTION()
	FFileData& GetFileData();

	UFUNCTION()
	FString GetTextContent();

	UFUNCTION()
	void SetTextContent(FString InText);
};
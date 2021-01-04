// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DiskNode.h"
#include "VirtualFileSystem.generated.h"

class URedemptionSaveGame;

/**
 * 
 */
UCLASS()
class REDEMPTION_API UVirtualFileSystem : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY()
	URedemptionSaveGame* SaveGame;
	
	UPROPERTY()
	UDiskNode* RootDiskNode;
	
public:
	UFUNCTION()
	void MountRootNode(URedemptionSaveGame* InSaveGame, int InMountId);
};

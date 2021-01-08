// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SAveGame.h"
#include "Wallpaper.h"
#include "SocialGuiState.h"
#include "DirectoryEntry.h"
#include "RedemptionSaveGame.generated.h"

/**
 * Stores all of the player's progress and important game state.
 */
UCLASS(BlueprintType)
class REDEMPTION_API URedemptionSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<FString> PlayerContacts;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TMap<int, int> DiskRoots;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<FDirectoryEntry> Directories;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int Experience;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int Level;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int UpgradePoints;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<FName> UnlockedUpgrades;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UWallpaper* DesktopWallpaper;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int GuiOpenConsoles;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	ESocialGuiState LastSocialState;

public:
	UFUNCTION()
	bool FindDirectoryIndex(int DirectoryId, int& OutDirectoryIndex);

	UFUNCTION()
	int GetAvailableDirectoryId();
};

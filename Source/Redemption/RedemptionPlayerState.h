﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ProgressionLevel.h"
#include "VirtualFileSystem.h"
#include "RedemptionPlayerState.generated.h"

class URedemptionGameInstance;
class UUpgradeAsset;
class UUserWidget;
class ARedemptionGameState;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUserLevelUp, FProgressionLevel, InLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUpgradeUnlocked);

UCLASS()
class REDEMPTION_API ARedemptionPlayerState : public APlayerState
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UVirtualFileSystem* VirtualFileSystem;
	
	UPROPERTY()
	UUserWidget* Desktop;
	
	UPROPERTY()
	ARedemptionGameState* GameState;
	
	UPROPERTY()
	int LevelStartXP;
	
	UPROPERTY()
	URedemptionGameInstance* GameInstance;

	UPROPERTY()
	class ARedemptionGameModeBase* GameMode;
	
	UPROPERTY()
	int Level;

	UPROPERTY()
	int TotalXP;

	UPROPERTY()
	int XPNeededForNextLevel;

	UPROPERTY()
	FString LevelName;

	UPROPERTY()
	TArray<UUpgradeAsset*> AvailableUpgrades;

	UPROPERTY()
	TArray<UUpgradeAsset*> UnlockedUpgrades;

	UPROPERTY()
	TArray<UUpgradeAsset*> UnavailableUpgrades;
	
public:
	// Sets default values for this actor's properties
	ARedemptionPlayerState();

public:
	UPROPERTY(BlueprintAssignable)
	FOnUserLevelUp OnLevelUp;

	UPROPERTY(BlueprintAssignable)
	FOnUpgradeUnlocked OnUpgradeUnlocked;
	
private:
	UFUNCTION()
	void UpdateSkillState();

	UFUNCTION()
	void SortUpgrades();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintPure)
	UVirtualFileSystem* GetFileSystem();
	
	UFUNCTION()
	class URedemptionSaveGame* GetSaveGame();

	UFUNCTION()
	bool RemoveUpgradePoints(int Amount);

	UFUNCTION()
	void NotifyUpgradeUnlocked();
	
public:
	UFUNCTION(BlueprintPure)
	TArray<UUpgradeAsset*> GetAvailableUpgrades();

	UFUNCTION(BlueprintPure)
    TArray<UUpgradeAsset*> GetUnlockedUpgrades();
	
	UFUNCTION(BlueprintPure)
	FString GetLevelName();

	UFUNCTION(BlueprintPure)
	int GetTotalXP();

	UFUNCTION(BlueprintPure)
	int GetXPNeededForLevel();

	UFUNCTION(BlueprintPure)
	int GetLevel();
	
	UFUNCTION(BlueprintPure)
	float GetLevelPercentage();

	UFUNCTION(BlueprintPure)
	int GetUpgradePoints();

	UFUNCTION(BlueprintPure)
	bool IsUpgradeUnlocked(UUpgradeAsset* Upgrade);
};

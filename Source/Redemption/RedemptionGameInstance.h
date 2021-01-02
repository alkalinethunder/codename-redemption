// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Profile.h"
#include "RedemptionSaveGame.h"
#include "RedemptionGameInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnExperienceAdded);

/**
 * Manages the state of Unreal Engine and the game across levels. 
 */
UCLASS()
class REDEMPTION_API URedemptionGameInstance : public UGameInstance
{
	GENERATED_BODY()

private:
	UPROPERTY()
	URedemptionSaveGame* CurrentGameSave;

	UPROPERTY()
	int CurrentGameSlot = -1;
	
	UPROPERTY()
	UProfile* Profile;

	UPROPERTY()
	FString ProfileSlotName;

public:
	UPROPERTY()
	FOnExperienceAdded OnExperienceAdded;
	
private:
	UFUNCTION()
	void SaveProfile();

	UFUNCTION()
	FSaveSlot& GetSlotInfo();

protected:
	virtual void Init() override;
	virtual void Shutdown() override;

public:
	UFUNCTION(BlueprintPure, Category="Redemption|Saves")
	bool DoesAnySlotExist();

	UFUNCTION(BlueprintPure, Category="Redemption|Saves")
	bool IsPlayerNameAvailable(FString InPlayerName);
	
	UFUNCTION(BlueprintPure, Category="Redemption|Saves")
	bool GetLastPlayedGame(FSaveSlot& OutSlot, int& OutSlotIndex);

	UFUNCTION(BlueprintCallable, Category="Redemption|Saves")
	void CreateGameSlot(FString InPlayerName);

	UFUNCTION(BlueprintCallable, Category="Redemption|Saves")
	bool ContinueGame(int SlotIndex);

public:
	UFUNCTION()
	void StartSession(class ARedemptionGameModeBase* GameMode);

	UFUNCTION()
	void EndSession();
	
	UFUNCTION()
	void SaveGame();

	UFUNCTION()
	URedemptionSaveGame* GetSaveGame();

public: // cheats/internal functions
	UFUNCTION(Exec)
	void AddXP(int Amount);

	UFUNCTION(Exec)
	void AddUpgradePoints(int Amount);
};

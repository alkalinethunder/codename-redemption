// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ProgressionLevel.h"
#include "RedemptionPlayerState.generated.h"

class URedemptionGameInstance;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUserLevelUp, FProgressionLevel, InLevel);

UCLASS()
class REDEMPTION_API ARedemptionPlayerState : public APlayerState
{
	GENERATED_BODY()

private:
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
	
public:
	// Sets default values for this actor's properties
	ARedemptionPlayerState();

public:
	UPROPERTY(BlueprintAssignable)
	FOnUserLevelUp OnLevelUp;
	
private:
	UFUNCTION()
	void UpdateSkillState();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
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
};

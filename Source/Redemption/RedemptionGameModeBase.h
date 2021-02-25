// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Wallpaper.h"
#include "SpecialDeviceAsset.h"
#include "NetworkAsset.h"
#include "ProgressionLevelsListAsset.h"
#include "DesktopWidget.h"
#include "ConsoleWidget.h"
#include "DesktopEnvironment.h"
#include "Shell.h"
#include "ShellCommandAsset.h"
#include "GraphicalAppAsset.h"
#include "WeekDay.h"
#include "RedemptionGameModeBase.generated.h"

class URedemptionGameInstance;
class ARedemptionPlayerState;
class AShellManagementActor;
class UNetPage;
class UUserContext;

/**
 * 
 */
UCLASS()
class REDEMPTION_API ARedemptionGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TArray<UNetworkAsset*> NetworkAssets;

	UPROPERTY()
	TArray<USpecialDeviceAsset*> SpecialDevices;
	
	UPROPERTY()
	TArray<UNetPage*> NetPages;
	
	UPROPERTY()
	TArray<UGraphicalAppAsset*> Apps;
	
	UPROPERTY()
	TArray<UShellCommandAsset*> ShellCommands;
	
	UPROPERTY()
	AShellManagementActor* ShellManager;
	
	UPROPERTY()
	URedemptionGameInstance* GameInstance;
	
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Hacking")
	float TraceTimeout = 120.f;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Progression")
    int StartingExperiencePoints;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Progression")
    int StartingUpgradePoints;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="World")
	UNetPage* DefaultNetBrowserHomePage;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Progression")
	UProgressionLevelsListAsset* LevelsList;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Progression")
	UDesktopEnvironment* DesktopWidget;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "OS")
	FString PlayerHostName = "localhost";

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "OS")
	FString PlayerUserName = "user";
	
    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "OS")
    bool bDoNotDisturbEnabled = false;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "OS")
    UWallpaper* DefaultWallpaper;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "World")
	float TimeScale = 1.f;	

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "World")
	EWeekDay DayOfWeek;

public:
	ARedemptionGameModeBase();

private:
	UFUNCTION()
	void SpawnSpecialDevices();
	
	UFUNCTION()
	void GenerateNetworks();
	
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	UFUNCTION(BlueprintCallable)
	UShell* CreateShell(UConsoleWidget* InConsoleWidget, UUserContext* InUserContext, bool InLoginShell = false);

	UFUNCTION()
	UNetPage* FindNetPage(FString InHost);
	
	UFUNCTION()
	UGraphicalAppAsset* FindApp(FString InName);
	
	UFUNCTION()
	UShellCommandAsset* FindCommand(FString InName);

	UFUNCTION()
	TArray<UGraphicalAppAsset*> GetPrograms();
	
	UFUNCTION()
	TArray<UShellCommandAsset*> GetCommands();
	
	UFUNCTION()
	TArray<UGraphicalAppAsset*> GetStartupApps();
};

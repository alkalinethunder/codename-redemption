// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Wallpaper.h"
#include "ProgressionLevelsListAsset.h"
#include "RedemptionGameModeBase.generated.h"

class UDesktopWidget;
class URedemptionGameInstance;
class ARedemptionPlayerState;
class AShellManagementActor;
class UConsoleWidget;
class UShell;
class UShellCommandAsset;
class UGraphicalAppAsset;

/**
 * 
 */
UCLASS()
class REDEMPTION_API ARedemptionGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TArray<UGraphicalAppAsset*> Apps;
	
	UPROPERTY()
	TArray<UShellCommandAsset*> ShellCommands;
	
	UPROPERTY()
	AShellManagementActor* ShellManager;
	
	UPROPERTY()
	URedemptionGameInstance* GameInstance;
	
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Progression")
    int StartingExperiencePoints;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Progression")
    int StartingUpgradePoints;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Progression")
	UProgressionLevelsListAsset* LevelsList;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Progression")
	TSubclassOf<UDesktopWidget> DesktopWidget;
	
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

public:
	ARedemptionGameModeBase();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	UFUNCTION(BlueprintCallable)
	UShell* CreateShell(UConsoleWidget* InConsoleWidget, bool InLoginShell = false);
	
	UFUNCTION()
	UShellCommandAsset* FindCommand(FString InName);

	UFUNCTION()
	TArray<UGraphicalAppAsset*> GetPrograms();
	
	UFUNCTION()
	TArray<UShellCommandAsset*> GetCommands();
	
	UFUNCTION()
	TArray<UGraphicalAppAsset*> GetStartupApps();
};

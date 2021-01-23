﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RedemptionPlayerController.h"
#include "UObject/Object.h"
#include "Shell.generated.h"

class UConsoleWidget;
class UCommandScript;
class AShellManagementActor;
class UUsefulTip;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FShellExitedEvent);

/**
 * In-game command shell.
 */
UCLASS(BlueprintType)
class REDEMPTION_API UShell : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY()
	FString Hostname;

	UPROPERTY()
	FString Username;
	
	UPROPERTY()
	TArray<UUsefulTip*> UsefulTips;
	
	UPROPERTY()
	bool bExited = false;
	
	UPROPERTY()
	bool IsLoginShell = false;

	UPROPERTY()
	FCommandFlags CurrentCommandFlags;
	
	UPROPERTY()
	UCommandScript* CurrentCommandScript;
	
	UPROPERTY()
	ARedemptionPlayerController* PlayerController;
	
	UPROPERTY()
	FString WorkingDirectory = "/";
	
	UPROPERTY()
	AShellManagementActor* ShellManager;
	
	UPROPERTY()
	UConsoleWidget* Console;

public:
	UPROPERTY(BlueprintAssignable)
	FShellExitedEvent OnExited;
	
private:
	UFUNCTION()
	void PrepareFileSystem();
	
	UFUNCTION()
	void PrintUsefulTips();

	UFUNCTION()
	void PrintCommands();

	UFUNCTION()
	void PrintPrograms();
	
	UFUNCTION()
	void Exit();
	
	UFUNCTION()
	void HandleConsoleTextSubmitted(FString InText);
	
	UFUNCTION()
	void HandleCompletedScript();
	
	UFUNCTION()
	void WritePrompt();

	UFUNCTION()
	bool BreakCommandLine(FString InText, TArray<FString>& OutParts, FString& OutError);

	UFUNCTION()
	bool ProcessBuiltin(FString InName, TArray<FString> InArgs);

	UFUNCTION()
	bool ProcessExtern(FString InName, TArray<FString> InArgs);
	
public:
	UFUNCTION()
	bool RequestExit();
	
	UFUNCTION()
	void LinkToConsole(AShellManagementActor* Owner, UConsoleWidget* InConsole);

	UFUNCTION()
	void MakeLoginShell();
};
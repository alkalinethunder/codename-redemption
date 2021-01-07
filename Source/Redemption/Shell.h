// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RedemptionPlayerController.h"
#include "UObject/Object.h"
#include "Shell.generated.h"

class UConsoleWidget;
class UCommandScript;
class AShellManagementActor;

/**
 * In-game command shell.
 */
UCLASS()
class REDEMPTION_API UShell : public UObject
{
	GENERATED_BODY()

private:
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

private:
	UFUNCTION()
	void HandleConsoleTextSubmitted(FString InText);

	UPROPERTY()
	FCommandFlags CurrentCommandFlags;
	
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
	void LinkToConsole(AShellManagementActor* Owner, UConsoleWidget* InConsole);
};
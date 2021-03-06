﻿#pragma once

#include "CoreMinimal.h"
#include "CommandScript.h"
#include "HackableType.h"
#include "EntryPoint.h"
#include "HackerShell.generated.h"

class UHackSession;

UCLASS(BlueprintType)
class REDEMPTION_API UHackerShell : public UCommandScript
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UHackSession* CurrentHack;
	
	UPROPERTY()
	FString HackedHost;

private:
	UFUNCTION()
	void UnbindEvents();
	
	UFUNCTION()
	bool HandleCommand(FString InName, TArray<FString> InArguments);
	
	UFUNCTION()
	void HandleCommandLine(FString InCommandLine);

	UFUNCTION()
	void WritePrompt();
	
protected:
	virtual void NativeRun() override;;
};
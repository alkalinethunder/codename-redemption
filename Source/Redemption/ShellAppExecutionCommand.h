// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommandScript.h"
#include "ShellAppExecutionCommand.generated.h"

class UGraphicalAppAsset;
class ARedemptionPlayerController;

/**
 * 
 */
UCLASS(BlueprintType)
class REDEMPTION_API UShellAppExecutionCommand : public UCommandScript
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UGraphicalAppAsset* AppAsset = nullptr;

	UPROPERTY()
	ARedemptionPlayerController* PlayerController;

protected:
	virtual void NativeRun() override;
	
public:
	UFUNCTION()
	void SetApp(UGraphicalAppAsset* InApp, ARedemptionPlayerController* InPlayerController);
};

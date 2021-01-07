// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ConsoleWidget.h"
#include "Blueprint/UserWidget.h"
#include "ShellHostWidget.generated.h"

class UShell;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, Abstract)
class REDEMPTION_API UShellHostWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UShell* Shell;
	
protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UConsoleWidget* Console;

public:
	UFUNCTION()
	bool RequestExit();
	
	UFUNCTION()
	bool InitShell(bool InLoginShell);
};

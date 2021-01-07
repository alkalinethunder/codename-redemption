// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ConsoleWidget.h"
#include "Blueprint/UserWidget.h"
#include "ShellHostWidget.generated.h"

class UShell;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnShellHostExit);

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, Abstract)
class REDEMPTION_API UShellHostWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY()
	bool bIHaveAlreadyFuckingDoneThis = false;
	
	UPROPERTY()
	UShell* Shell;
	
protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UConsoleWidget* Console;

public:
	UPROPERTY(BlueprintAssignable)
	FOnShellHostExit OnShellExit;
	
private:
	UFUNCTION()
	void HandleShellExited();
	
public:
	UFUNCTION()
	bool RequestExit();
	
	UFUNCTION()
	bool InitShell(bool InLoginShell);
};

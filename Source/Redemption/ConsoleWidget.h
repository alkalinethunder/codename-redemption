// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ConsoleTextData.h"
#include "Fonts/SlateFontInfo.h"
#include "ConsoleWidget.generated.h"

/**
 * Renders the in-game console.
 */
UCLASS(BlueprintType, Blueprintable)
class REDEMPTION_API UConsoleWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TArray<FConsoleTextData> DrawItems;
	
	UPROPERTY()
	FString InputBuffer;

	UPROPERTY()
	FString OutputBuffer;

	UPROPERTY()
	int InputPos;

	UPROPERTY()
	TArray<FString> History;

	UPROPERTY()
	TArray<FString> Future;
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Appearance")
	FSlateFontInfo Font;

public:
	UFUNCTION(BlueprintCallable)
	void Write(FText InText);

	UFUNCTION(BlueprintCallable)
	void WriteLine(FText InText);

	UFUNCTION(BlueprintCallable)
	void ClearScreen();
};

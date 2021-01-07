// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ConsoleTextData.h"
#include "Fonts/SlateFontInfo.h"
#include "Components/SizeBox.h"
#include "ConsoleWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnConsoleTextWritten);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTextSubmitted, FString, InText);

/**
 * Renders the in-game console.
 */
UCLASS(BlueprintType, Blueprintable)
class REDEMPTION_API UConsoleWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	TCHAR ColorDelimeter = '%';

	UPROPERTY()
	int ScrollBack = 0;

	UPROPERTY()
	float TextHeight;
	
	UPROPERTY()
	bool TextIsDirty = true;

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
	float CharWidth;

	UPROPERTY()
	float CharHeight;
	
	UPROPERTY()
	TArray<FString> Future;

public:
	UPROPERTY(BlueprintAssignable)
	FOnTextSubmitted OnTextSubmitted;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FSlateBrush Brush;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Appearance")
	FSlateFontInfo Font;

private:
	UFUNCTION()
	void MeasureText(FString InText, int& OutWidth, int& OutHeight);
	
	UFUNCTION()
	FString StripFormatting(FString InText);
	
	UFUNCTION()
	void RebuildTextItems(const FGeometry& MyGeometry);

	UFUNCTION()
    void RecalculateTextSizes_Pass2(const FGeometry& MyGeometry);
	
	UFUNCTION()
	void RecalculateTextSizes();
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;
	virtual FReply NativeOnKeyChar(const FGeometry& InGeometry, const FCharacterEvent& InCharEvent) override;
	virtual bool NativeIsInteractable() const override;
	virtual bool NativeSupportsKeyboardFocus() const override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

public:
	UPROPERTY(BlueprintAssignable)
	FOnConsoleTextWritten OnTextWritten;
	
public:
	UFUNCTION(BlueprintCallable)
	void Write(FText InText);

	UFUNCTION(BlueprintCallable)
	void WriteLine(FText InText);

	UFUNCTION(BlueprintCallable)
	void ClearScreen();
};

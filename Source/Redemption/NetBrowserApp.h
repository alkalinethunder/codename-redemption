// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AppWidget.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Components/ScrollBox.h"
#include "WebBrowser.h"
#include "NetBrowserApp.generated.h"

class ARedemptionGameModeBase;

UCLASS(BlueprintType, Blueprintable, Abstract)
class REDEMPTION_API UNetBrowserApp : public UAppWidget
{
	GENERATED_BODY()

private:	
	UPROPERTY()
	ARedemptionGameModeBase* GameMode;
	
	UPROPERTY()
	FString CurrentUrl;
	
	UPROPERTY()
	TArray<FString> History;

	UPROPERTY()
	TArray<FString> Future;
	
protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UWebBrowser* HtmlBrowser;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UEditableText* AddressBar;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UButton* GoButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UButton* BackButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UButton* ForwardButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UScrollBox* WebContent;

private:
	UFUNCTION()
	bool IsHttp(FString InProtocol);
	
	UFUNCTION()
	void HandleAddressSubmission(const FText& InText, ETextCommit::Type InCommitType);
	
	UFUNCTION()
	void HandleHtmlUrlChanged(const FText& InText);
	
	UFUNCTION()
	void HandleGoButton();
	
	UFUNCTION()
	void NavigateInternal(FString InUrl, bool AddToHistory);
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UFUNCTION(BlueprintCallable)
	void GoBack();

	UFUNCTION(BlueprintCallable)
	void GoForward();

	UFUNCTION(BlueprintCallable)
	void NavigateToUrl(FString InUrl);
};

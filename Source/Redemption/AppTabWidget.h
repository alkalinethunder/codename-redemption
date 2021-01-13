// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "AppTabWidget.generated.h"

/**
 * Base widget for a graphical app tab.
 */
UCLASS(Blueprintable, BlueprintType, Abstract)
class REDEMPTION_API UAppTabWidget : public UUserWidget
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAppTabCloseRequested, UAppTabWidget*, RequestingWidget);
	
protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category = "App Tab")
	UTextBlock* TitleText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category = "App Tab")
	UImage* Icon;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category = "App Tab")
	UButton* AppTrigger;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget), Category = "App Tab")
	UButton* CloseTrigger;
	
protected:
	virtual void NativeConstruct() override;
	
public:
	UPROPERTY()
	UWidgetSwitcher* WidgetSwitcher;

	UPROPERTY()
	int TrackedIndex;

	UPROPERTY(BlueprintReadOnly, Category = "App Tab")
	UTexture2D* AppIcon;
	
	UPROPERTY(BlueprintReadOnly, Category = "App Tab")
	FText AppTitle;

	UPROPERTY(BlueprintReadOnly, Category = "App Tab")
	bool IsCloseable;

	UPROPERTY(BlueprintAssignable, Category = "App Tab")
	FOnAppTabCloseRequested OnCloseRequested;
	
public:
	UFUNCTION()
    void RequestClose();
	
	UFUNCTION(BlueprintCallable)
    void SwitchToApp();
	
	UFUNCTION(BlueprintPure, Category = "App Tab")
	bool IsActiveApp();
};


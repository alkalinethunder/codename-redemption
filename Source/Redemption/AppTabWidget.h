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
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* TitleText;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* Icon;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UButton* AppTrigger;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UButton* CloseTrigger;
	
protected:
	virtual void NativeConstruct() override;
	
public:
	UPROPERTY()
	UWidgetSwitcher* WidgetSwitcher;

	UPROPERTY()
	int TrackedIndex;

	UPROPERTY(BlueprintReadOnly)
	UTexture2D* AppIcon;
	
	UPROPERTY(BlueprintReadOnly)
	FText AppTitle;

	UPROPERTY(BlueprintReadOnly)
	bool IsCloseable;

	UPROPERTY(BlueprintAssignable)
	FOnAppTabCloseRequested OnCloseRequested;
	
public:
	UFUNCTION()
    void RequestClose();
	
	UFUNCTION()
    void SwitchToApp();
	
	UFUNCTION(BlueprintPure)
	bool IsActiveApp();
};


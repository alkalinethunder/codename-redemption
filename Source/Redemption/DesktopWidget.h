// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Components/WidgetSwitcher.h"

#include "DesktopWidget.generated.h"

/**
 * Base widget for desktop UIs.
 */
UCLASS(Blueprintable, BlueprintType, Abstract)
class REDEMPTION_API UDesktopWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UWidgetSwitcher* ConsoleSwitcher;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UWidgetSwitcher* ProgramSwitcher;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UWidgetSwitcher* SocialSwitcher;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UHorizontalBox* SocialTabs;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UHorizontalBox* ProgramTabs;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UHorizontalBox* ConsoleTabs;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UButton* CreateShellTrigger;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UButton* DoNotDisturbToggle;
};

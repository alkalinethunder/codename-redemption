// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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
};

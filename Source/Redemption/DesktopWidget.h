// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Components/WidgetSwitcher.h"
#include "DesktopWidget.generated.h"

class UAppTabWidget;
class UShellHostWidget;
class UOperatingSystemApp;
class UAppHostWidget;
class ARedemptionGameModeBase;
class UGraphicalAppAsset;

/**
 * Base widget for desktop UIs.
 */
UCLASS(Blueprintable, BlueprintType, Abstract)
class REDEMPTION_API UDesktopWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY()
	ARedemptionGameModeBase* GameMode;
	
protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UAppTabWidget> AppTabWidgetClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UShellHostWidget> ShellHostWidgetClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UAppHostWidget> AppHostWidgetClass;
	
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

private:
	UFUNCTION()
	void HandleShellClose(UAppTabWidget* RequestingWidget);
	
	UFUNCTION()
	void HandleAppClose(UAppTabWidget* RequestingWidget);
	
	UFUNCTION()
	void CreateShell();
	
	UFUNCTION()
	void LaunchShellInternal(bool InLoginShell);
	
	UFUNCTION()
	UOperatingSystemApp* LaunchTabbedApp(UWidgetSwitcher* InWidgetSwitcher, UHorizontalBox* InTabsPanel, UGraphicalAppAsset* InApp);
	
	UFUNCTION()
	UOperatingSystemApp* LaunchAppInternal(UGraphicalAppAsset* InApp);
	
protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION()
	bool SwitchToApp(TSubclassOf<UUserWidget> InWidgetClass, UOperatingSystemApp*& OutWidget);

	UFUNCTION()
	bool LaunchApp(UGraphicalAppAsset* InApp, UOperatingSystemApp*& OutWidget);
};

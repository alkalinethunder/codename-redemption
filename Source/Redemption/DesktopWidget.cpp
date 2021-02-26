// Fill out your copyright notice in the Description page of Project Settings.


#include "DesktopWidget.h"
#include "OperatingSystemApp.h"
#include "AppTabWidget.h"
#include "AppHostWidget.h"
#include "GraphicalAppAsset.h"
#include "ShellHostWidget.h"
#include "RedemptionGameModeBase.h"
#include "AppWidget.h"
#include "RedemptionGameState.h"
#include "RedemptionPlayerState.h"

void UDesktopWidget::ToggleDND()
{
	this->MyGameState->ToggleDoNotDisturb();
}

void UDesktopWidget::HandleShellClose(UAppTabWidget* RequestingWidget)
{
	UShellHostWidget* ShellHost = Cast<UShellHostWidget>(RequestingWidget->WidgetSwitcher->GetChildAt(RequestingWidget->TrackedIndex));

	if (ShellHost)
	{
		if (!ShellHost->RequestExit())
			return;
	}
	
	this->HandleAppClose(RequestingWidget);
}

void UDesktopWidget::HandleAppClose(UAppTabWidget* RequestingWidget)
{
	if (RequestingWidget->IsActiveApp())
	{
		RequestingWidget->WidgetSwitcher->SetActiveWidgetIndex(RequestingWidget->TrackedIndex - 1);
	}

	RequestingWidget->WidgetSwitcher->RemoveChildAt(RequestingWidget->TrackedIndex);

	UHorizontalBox* parentBox = Cast<UHorizontalBox>(RequestingWidget->GetParent());

	if (parentBox)
	{
		for (int i = 0; i < parentBox->GetChildrenCount(); i++)
		{
			UAppTabWidget* tab = Cast<UAppTabWidget>(parentBox->GetChildAt(i));
			if (tab)
			{
				if (tab->TrackedIndex > RequestingWidget->TrackedIndex)
				{
					tab->TrackedIndex--;
				}
			}
		}
	}
	
	RequestingWidget->RemoveFromParent();
}

void UDesktopWidget::CreateShell()
{
	this->LaunchShellInternal(false);
}

void UDesktopWidget::LaunchShellInternal(bool InLoginShell)
{
	check (this->ShellHostWidgetClass);

	// Create the shell host.
	UShellHostWidget* ShellHost = CreateWidget<UShellHostWidget, APlayerController>(this->GetOwningPlayer(), this->ShellHostWidgetClass);

	check (ShellHost);

	// create an App Tab.
	check (this->AppTabWidgetClass);
	UAppTabWidget* AppTab = CreateWidget<UAppTabWidget, APlayerController>(this->GetOwningPlayer(), this->AppTabWidgetClass);

	check (AppTab);

	// Where will we put it?
	int WidgetIndex = (this->ConsoleSwitcher->GetChildrenCount() > 0) ? this->ConsoleSwitcher->GetActiveWidgetIndex() + 1 : 0;

	// Set the tab data.
	AppTab->TrackedIndex = WidgetIndex;
	AppTab->WidgetSwitcher = this->ConsoleSwitcher;
	AppTab->AppTitle = FText::FromString("Shell");
	AppTab->IsCloseable = !InLoginShell;

	// bind to close requests.
	AppTab->OnCloseRequested.AddUniqueDynamic(this, &UDesktopWidget::UDesktopWidget::HandleShellClose);

	// handle the shell exit event
	ShellHost->OnShellExit.AddUniqueDynamic(AppTab, &UAppTabWidget::RequestClose);
	
	// Add the app tab and the shell host.
	this->ConsoleSwitcher->InsertChildAt(WidgetIndex, ShellHost);
	this->ConsoleTabs->InsertChildAt(WidgetIndex, AppTab);

	// Switch to the shell
	this->ConsoleSwitcher->SetActiveWidgetIndex(WidgetIndex);
	
	// Initialize the shell.
	ShellHost->InitShell(this->CurrentContext, InLoginShell);
}

UOperatingSystemApp* UDesktopWidget::LaunchTabbedApp(UWidgetSwitcher* InWidgetSwitcher, UHorizontalBox* InTabsPanel,
                                     UGraphicalAppAsset* InApp)
{
	// assert any null arguments
	check (InWidgetSwitcher);
	check (InTabsPanel);
	check (InApp);

	// spawn the app's UI.
	UAppWidget* AppWidget = CreateWidget<UAppWidget, APlayerController>(this->GetOwningPlayer(), InApp->WidgetClass);

	// and assert if it failed.
	check (AppWidget);

	// Create the app tab.
	UAppTabWidget* AppTab = CreateWidget<UAppTabWidget, APlayerController>(this->GetOwningPlayer(), this->AppTabWidgetClass);

	// assert it.
	check (AppTab);

	// where will we place the tab and widget?
	int WidgetIndex = (InWidgetSwitcher->GetChildrenCount() > 0) ? InWidgetSwitcher->GetActiveWidgetIndex() + 1 : 0;

	// Assign the data to the app tab.
	AppTab->TrackedIndex = WidgetIndex;
	AppTab->WidgetSwitcher = InWidgetSwitcher;
	AppTab->AppIcon = InApp->Icon;
	AppTab->AppTitle = InApp->Title;
	AppTab->IsCloseable = InApp->CommandFlags.IsUserCloseable;
	
	// Spawn in the tab.
	InTabsPanel->InsertChildAt(WidgetIndex, AppTab);

	// bind to close requests.
	AppTab->OnCloseRequested.AddUniqueDynamic(this, &UDesktopWidget::HandleAppClose);
	
	// Add the UI to the app switcher, and set it as the active index.
	// At this point, the app's UI is visible.
	InWidgetSwitcher->InsertChildAt(WidgetIndex, AppWidget);
	InWidgetSwitcher->SetActiveWidgetIndex(WidgetIndex);

	UOperatingSystemApp* NewApp = NewObject<UOperatingSystemApp>();
	NewApp->AppWidget = AppWidget;
	NewApp->TabWidget = AppTab;
	NewApp->AppAsset = InApp;
	
	return NewApp;
}

UOperatingSystemApp* UDesktopWidget::LaunchInfoApp(UVerticalBox* InInfoBox, UGraphicalAppAsset* InApp)
{
	check (this->CollapseableAppClass);
	check (InInfoBox);
	check (InApp);

	UCollapseableApp* collapseable = CreateWidget<UCollapseableApp, APlayerController>(this->GetOwningPlayer(), this->CollapseableAppClass);
	UAppWidget* AppWidget = CreateWidget<UAppWidget, APlayerController>(this->GetOwningPlayer(), InApp->WidgetClass);
	
	UOperatingSystemApp* NewApp = NewObject<UOperatingSystemApp>();
	NewApp->AppAsset = InApp;
	NewApp->AppWidget = AppWidget;

	InInfoBox->AddChildToVerticalBox(collapseable);
	collapseable->BindApp(NewApp);
	
	return NewApp;
}

UOperatingSystemApp* UDesktopWidget::LaunchAppInternal(UGraphicalAppAsset* InApp)
{
	UOperatingSystemApp* result = nullptr;
	check (InApp);
	check (InApp->WidgetClass);
	check (this->AppHostWidgetClass);
	check (this->AppTabWidgetClass);

	switch (InApp->DisplayTarget)
	{
		case EDisplayTarget::Default:
			result = this->LaunchTabbedApp(this->ProgramSwitcher, this->ProgramTabs, InApp);
			break;
		case EDisplayTarget::Social:
			result = this->LaunchTabbedApp(this->SocialSwitcher, this->SocialTabs, InApp);
			break;
		case EDisplayTarget::InfoWidgets:
			result = this->LaunchInfoApp(this->InfoBox, InApp);
			break;
		default:
			result = nullptr;
			break;
	}

	return result;
}

void UDesktopWidget::NativeConstruct()
{
	Super::NativeConstruct();

	this->MyGameState = Cast<ARedemptionGameState>(this->GetWorld()->GetGameState());
	this->GameMode = Cast<ARedemptionGameModeBase>(this->GetWorld()->GetAuthGameMode());

	// This is the OS context of the player. Commands and Apps all need this.
	this->CurrentContext = Cast<ARedemptionPlayerState>(this->GetOwningPlayerState())->GetPlayerUserContext();
	
	// launch the login shell.
	this->LaunchShellInternal(true);
	
	for (UGraphicalAppAsset* gapp : this->GameMode->GetStartupApps())
	{
		// launch the app.
		this->LaunchAppInternal(gapp);
	}

	this->CreateShellTrigger->OnClicked.AddUniqueDynamic(this, &UDesktopWidget::CreateShell);

	this->DoNotDisturbToggle->OnClicked.AddUniqueDynamic(this, &UDesktopWidget::ToggleDND);
}

void UDesktopWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	int hour = this->MyGameState->GetHour();
	int minute = this->MyGameState->GetMinute();

	FString minText = minute >= 10 ? FString::FromInt(minute) : "0" + FString::FromInt(minute);
	FString hourText = FString::FromInt(hour > 12 ? hour - 12 : hour);

	this->TimeOfDay->SetText(FText::FromString(hourText + ":" + minText));
}

bool UDesktopWidget::SwitchToApp(TSubclassOf<UAppWidget> InWidgetClass, UOperatingSystemApp*& OutWidget)
{
	for (int i = 0; i < this->ProgramTabs->GetChildrenCount(); i++)
	{
		UAppTabWidget* tab = Cast<UAppTabWidget>(this->ProgramTabs->GetChildAt(i));
		if (tab)
		{
			UAppWidget* child = Cast<UAppWidget>(this->ProgramSwitcher->GetChildAt(tab->TrackedIndex));

			if (child && child->GetClass() == InWidgetClass)
			{
				OutWidget = NewObject<UOperatingSystemApp>();
				OutWidget->AppWidget = child;
				OutWidget->TabWidget = tab;
				
				this->ProgramSwitcher->SetActiveWidgetIndex(i);
				return true;
			}
		}
	}

	for (int i = 0; i < this->SocialTabs->GetChildrenCount(); i++)
	{
		UAppTabWidget* tab = Cast<UAppTabWidget>(this->SocialTabs->GetChildAt(i));
		if (tab)
		{
			UAppWidget* child = Cast<UAppWidget>(this->SocialSwitcher->GetChildAt(tab->TrackedIndex));

			if (child && child->GetClass() == InWidgetClass)
			{
				OutWidget = NewObject<UOperatingSystemApp>();
				OutWidget->AppWidget = child;
				OutWidget->TabWidget = tab;
				
				this->ProgramSwitcher->SetActiveWidgetIndex(i);
				return true;
			}
		}
	}

	return false;
}

bool UDesktopWidget::LaunchApp(UGraphicalAppAsset* InApp, UOperatingSystemApp*& OutWidget)
{
	UOperatingSystemApp* result = this->LaunchAppInternal(InApp);

	if (result)
	{
		OutWidget = result;
		return true;
	}
	else
	{
		return false;
	}
}

UUserContext* UDesktopWidget::GetUserContext()
{
	return this->CurrentContext;
}

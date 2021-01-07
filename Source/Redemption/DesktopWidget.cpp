// Fill out your copyright notice in the Description page of Project Settings.


#include "DesktopWidget.h"
#include "AppTabWidget.h"
#include "AppHostWidget.h"
#include "GraphicalAppAsset.h"
#include "ShellHostWidget.h"
#include "RedemptionGameModeBase.h"

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
	
	// Add the app tab and the shell host.
	this->ConsoleSwitcher->InsertChildAt(WidgetIndex, ShellHost);
	this->ConsoleTabs->InsertChildAt(WidgetIndex, AppTab);

	// Switch to the shell
	this->ConsoleSwitcher->SetActiveWidgetIndex(WidgetIndex);
	
	// Initialize the shell.
	ShellHost->InitShell(InLoginShell);
}

void UDesktopWidget::LaunchTabbedApp(UWidgetSwitcher* InWidgetSwitcher, UHorizontalBox* InTabsPanel,
                                     UGraphicalAppAsset* InApp)
{
	// assert any null arguments
	check (InWidgetSwitcher);
	check (InTabsPanel);
	check (InApp);

	// spawn the app's UI.
	UUserWidget* AppWidget = CreateWidget<UUserWidget, APlayerController>(this->GetOwningPlayer(), InApp->WidgetClass);

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
}

void UDesktopWidget::LaunchAppInternal(UGraphicalAppAsset* InApp)
{
	check (InApp);
	check (InApp->WidgetClass);
	check (this->AppHostWidgetClass);
	check (this->AppTabWidgetClass);

	switch (InApp->DisplayTarget)
	{
		case EDisplayTarget::Default:
			this->LaunchTabbedApp(this->ProgramSwitcher, this->ProgramTabs, InApp);
			break;
		case EDisplayTarget::Social:
			this->LaunchTabbedApp(this->SocialSwitcher, this->SocialTabs, InApp);
			break;
		default:
			check(false);
			break;
	}
}

void UDesktopWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	this->GameMode = Cast<ARedemptionGameModeBase>(this->GetWorld()->GetAuthGameMode());

	// launch the login shell.
	this->LaunchShellInternal(true);
	
	for (UGraphicalAppAsset* gapp : this->GameMode->GetStartupApps())
	{
		// launch the app.
		this->LaunchAppInternal(gapp);
	}

	this->CreateShellTrigger->OnClicked.AddUniqueDynamic(this, &UDesktopWidget::CreateShell);
}

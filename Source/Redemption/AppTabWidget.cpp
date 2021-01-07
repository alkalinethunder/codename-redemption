// Fill out your copyright notice in the Description page of Project Settings.


#include "AppTabWidget.h"

void UAppTabWidget::NativeConstruct()
{
	Super::NativeConstruct();

	this->AppTrigger->OnClicked.AddUniqueDynamic(this, &UAppTabWidget::SwitchToApp);
	this->CloseTrigger->OnClicked.AddUniqueDynamic(this, &UAppTabWidget::RequestClose);
}

void UAppTabWidget::RequestClose()
{
	this->OnCloseRequested.Broadcast(this);
}


bool UAppTabWidget::IsActiveApp()
{
	return this->WidgetSwitcher && this->WidgetSwitcher->GetActiveWidgetIndex() == this->TrackedIndex;
}

void UAppTabWidget::SwitchToApp()
{
	this->WidgetSwitcher->SetActiveWidgetIndex(this->TrackedIndex);
}

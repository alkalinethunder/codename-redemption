// Fill out your copyright notice in the Description page of Project Settings.


#include "ConversationInstance.h"
#include "ConversationManager.h"
#include "ConversationAppWidget.h"
#include "Conversation.h"

void UConversationInstance::LinkToManager(AConversationManager* InManager, UConversationAppWidget* InWidget, UConversation* InAsset)
{
	check(InAsset);
	check(InManager);
	check(InWidget);

	this->MyAsset = InAsset;
	this->ConversationManager = InManager;
	this->AppWidget = InWidget;

	this->AppWidget->SetConversation(this);
}

void UConversationInstance::SwitchUserInterface(UConversationAppWidget* InApp)
{
	if (this->AppWidget)
	{
		// TODO: unlink the UI.
		this->AppWidget = nullptr;
	}

	check(InApp);
	
	this->AppWidget = InApp;
	this->AppWidget->SetConversation(this);
}

UConversationAppWidget* UConversationInstance::GetUserInterface()
{
	return this->AppWidget;
}

void UConversationInstance::DoNotDisturbChanged(bool InDoNotDisturb)
{
	this->AppWidget->SetDoNotDisturb(InDoNotDisturb);
}

AConversationManager* UConversationInstance::GetConversationManager()
{
	return this->ConversationManager;
}

UConversation* UConversationInstance::GetConversationAsset()
{
	return this->MyAsset;
}

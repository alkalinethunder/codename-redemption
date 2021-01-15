// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatAction.h"
#include "ConversationInstance.h"

void UChatAction::NativeStateReset()
{
	this->StateReset();
}

void UChatAction::NativeBegin()
{
	this->Begin();
}

void UChatAction::NativeTick(float DeltaTime)
{
	this->Tick(DeltaTime);
}

void UChatAction::NativeEnd()
{
	this->End();
}

void UChatAction::Complete()
{
	this->bBegun = true;
	this->bFinished = true;
}

UConversationAppWidget* UChatAction::GetChatUserInterface()
{
	return this->Conversation->GetUserInterface();
}

UConversationInstance* UChatAction::GetConversation()
{
	return this->Conversation;
}

bool UChatAction::IsFinished()
{
	return this->bFinished;
}

void UChatAction::ResetState()
{
	this->NativeStateReset();

	this->bFinished = false;
	this->bBegun = false;

	this->Conversation = nullptr;
}

void UChatAction::Run(float DeltaTime, UConversationInstance* InConversationInstance)
{
	this->Conversation = InConversationInstance;
	
	if (!this->bBegun)
	{
		this->bBegun = true;
		this->NativeBegin();
	}

	if (!this->bFinished)
	{
		this->NativeTick(DeltaTime);
	}

	if (this->bFinished)
	{
		this->NativeEnd();
	}
}

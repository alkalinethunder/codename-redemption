// Fill out your copyright notice in the Description page of Project Settings.


#include "SendMessage.h"

#include "ConversationAppWidget.h"

void USendMessage::NativeTick(float DeltaTime)
{
	if (SecondsLeftInTypeDelay > 0)
	{
		this->bTyping = true;
		SecondsLeftInTypeDelay -= DeltaTime;
	}
	else if (SecondsLeftInSendDelay > 0)
	{
		if (this->bTyping)
		{
			if (this->Person)
			{
				this->GetChatUserInterface()->RemoveTyper(this->Person);
			}
			this->bTyping = false;
		}
		SecondsLeftInSendDelay -= DeltaTime;
	}
	else
	{
		this->Complete();
	}
}

void USendMessage::NativeEnd()
{
	if (this->Person)
	{
		this->GetChatUserInterface()->SendMessage(this->MessageText, FDateTime::UtcNow(), this->Person);
	}
	else
	{
		this->GetChatUserInterface()->SendPlayerMessage(this->MessageText, FDateTime::UtcNow());
	}
}

void USendMessage::NativeBegin()
{
	if (this->Person)
	{
		this->GetChatUserInterface()->AddTyper(this->Person);
	}
	
	this->SecondsLeftInTypeDelay = 0.05f * this->MessageText.ToString().Len();
	this->SecondsLeftInSendDelay = 0.5f;
}

void USendMessage::NativeStateReset()
{
	this->SecondsLeftInTypeDelay=0;
	this->SecondsLeftInSendDelay=0;
}

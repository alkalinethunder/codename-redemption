// Fill out your copyright notice in the Description page of Project Settings.


#include "SendMessage.h"

#include "ConversationAppWidget.h"

void USendMessage::UpdatePlayerMessageBox()
{
	float progress = 1.f - FMath::Clamp((this->SecondsLeftInTypeDelay / this->TotalTypeDelayTime), 0.f, 1.f);

	FString text = this->MessageText.ToString();
	int textLen = text.Len();

	int sliceAt = FMath::CeilToInt(progress * textLen);

	FString submission = text;
	if (sliceAt <= submission.Len())
	{
		submission = text.Left(sliceAt);
	}

	this->GetChatUserInterface()->SetPlayerMessageText(FText::FromString(submission));
}

void USendMessage::NativeTick(float DeltaTime)
{
	if (SecondsLeftInTypeDelay > 0)
	{
		this->bTyping = true;
		SecondsLeftInTypeDelay -= DeltaTime;

		if (!this->Person)
		{
			this->UpdatePlayerMessageBox();
		}
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
		this->GetChatUserInterface()->UnlockPlayerMessageBox();
	}
}

void USendMessage::NativeBegin()
{
	if (this->Person)
	{
		this->GetChatUserInterface()->AddTyper(this->Person);
	}
	else
	{
		this->GetChatUserInterface()->LockPlayerMessageBox();	
	}
	
	this->SecondsLeftInTypeDelay = 0.05f * this->MessageText.ToString().Len();
	this->TotalTypeDelayTime = this->SecondsLeftInTypeDelay;
	this->SecondsLeftInSendDelay = 0.5f;
}

void USendMessage::NativeStateReset()
{
	this->SecondsLeftInTypeDelay=0;
	this->SecondsLeftInSendDelay=0;
}

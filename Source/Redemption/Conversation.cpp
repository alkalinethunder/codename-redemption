// Fill out your copyright notice in the Description page of Project Settings.


#include "Conversation.h"

#include "RedemptionSaveGame.h"

bool UConversation::IsAvailable(URedemptionSaveGame* InSaveGame)
{
	bool result = true;
	
	if (InSaveGame)
	{
		if (!this->Contact)
		{
			result = false;
		}
		else if (!InSaveGame->PlayerContacts.Contains(this->Contact->GetName()));
		else if (this->IsFinished(InSaveGame))
		{
			result = false;
		}
		else
		{
			for (UConversation* required : this->RequiredConversations)
			{
				if (!required->IsFinished(InSaveGame))
				{
					result = false;
					break;
				}
			}
		}
	}
	else
	{
		result = false;
	}

	return result;
}

bool UConversation::IsFinished(URedemptionSaveGame* InSaveGame)
{
	return InSaveGame && InSaveGame->CompletedChats.Contains(this->GetName());
}

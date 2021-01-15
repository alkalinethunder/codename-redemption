// Fill out your copyright notice in the Description page of Project Settings.


#include "RedemptionSaveGame.h"

#include "AssetUtils.h"
#include "ChatContact.h"
#include "ConversationAppWidget.h"

bool URedemptionSaveGame::FindDirectoryIndex(int DirectoryId, int& OutDirectoryIndex)
{
	bool result = false;

	for (int i = 0; i < this->Directories.Num(); i++)
	{
		if (this->Directories[i].Id == DirectoryId)
		{
			OutDirectoryIndex = i;
			result = true;
			break;
		}
	}
	
	return result;
}

int URedemptionSaveGame::GetAvailableDirectoryId()
{
	TArray<int> used;
	int result;

	for (FDirectoryEntry& Entry : this->Directories)
	{
		used.Add(Entry.Id);
	}

	while (used.Contains(result))
		result++;
	
	return result;
}

void URedemptionSaveGame::PostChatLogs(UConversationAppWidget* InWidget, UChatContact* InContact)
{
	TMap<FString, UPerson*> contactMap;
	for (UObject* obj : UAssetUtils::LoadAssetsOfClass(UPerson::StaticClass()))
	{
		UPerson* contact = Cast<UPerson>(obj);
		if (contact)
		{
			contactMap.Add(contact->GetName(), contact);
		}
	}
	
	for (FChatLog& log : this->PlayerChatLogs)
	{
		if (log.Contact == InContact->GetName())
		{
			if (contactMap.Contains(log.Sender))
			{
				InWidget->SendMessage(log.MessageText, log.UtcSent, contactMap[log.Sender]);
			}
			else
			{
				InWidget->SendPlayerMessage(log.MessageText, log.UtcSent);
			}
		}
	}
}

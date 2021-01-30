// Fill out your copyright notice in the Description page of Project Settings.


#include "RedemptionSaveGame.h"

#include "AssetUtils.h"
#include "ChatContact.h"
#include "ConversationAppWidget.h"
#include "NetworkAsset.h"

int URedemptionSaveGame::FindNetwork(UNetworkAsset* InNetworkAsset)
{
	int result = -1;

	for (int i = 0; i < this->Networks.Num(); i++)
	{
		FNetwork net = this->Networks[i];
		if (net.AssetId == InNetworkAsset->GetName())
		{
			result = i;
			break;
		}
	}
	
	return result;
}

bool URedemptionSaveGame::DeviceTypeExistsInNetwork(const FNetwork& InNetwork, EDeviceType InDeviceType)
{
	bool result = false;
	
	for (const FDevice& dev : this->Devices)
	{
		if (InNetwork.Devices.Contains(dev.Id))
		{
			if (dev.DeviceType == InDeviceType)
			{
				result = true;
				break;
			}
		}
	}

	return result;
}

int URedemptionSaveGame::GetNextDeviceId()
{
	int result = 0;
	TArray<int> used;

	for (FDevice& dev : this->Devices)
	{
		used.Add(dev.Id);
	}

	while (used.Contains(result))
	{
		result++;
	}
	
	return result;
}

int URedemptionSaveGame::GetNextNetworkId()
{
	int result = 0;
	TArray<int> used;

	for (FNetwork& net : this->Networks)
	{
		used.Add(net.Id);
	}

	while (used.Contains(result))
	{
		result++;
	}
	
	return result;
}

bool URedemptionSaveGame::FindFileIndex(int InFileId, int& OutIndex)
{
	bool result = false;
	OutIndex = false;

	for (int i = 0; i < this->Files.Num(); i++)
	{
		if (this->Files[i].Id == InFileId)
		{
			result = true;
			OutIndex = i;
			break;
		}
	}
	
	return result;
}

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

int URedemptionSaveGame::GetAvailableFileId()
{
	int result = 0;
	TArray<int> used;
	for (FFileData& file : this->Files)
	{
		used.Add(file.Id);
	}

	while (used.Contains(result))
		result++;
	
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

// Fill out your copyright notice in the Description page of Project Settings.


#include "RedemptionSaveGame.h"

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

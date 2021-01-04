// Fill out your copyright notice in the Description page of Project Settings.


#include "VirtualFileSystem.h"
#include "RedemptionSaveGame.h"
#include "DirectoryNode.h"

void UVirtualFileSystem::MountRootNode(URedemptionSaveGame* InSaveGame, int InMountId)
{
	check(!this->SaveGame);
	check(!this->RootDiskNode);

	this->SaveGame = InSaveGame;

	UDirectoryNode* Directory = NewObject<UDirectoryNode>();

	int DirectoryIndex = this->SaveGame->DiskRoots[InMountId];

	Directory->LinkToDirectory(nullptr, this->SaveGame, DirectoryIndex);
	this->RootDiskNode = Directory;
}

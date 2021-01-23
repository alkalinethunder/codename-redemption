// Fill out your copyright notice in the Description page of Project Settings.


#include "DirectoryNode.h"
#include "RedemptionSaveGame.h"
#include "FileNode.h"

UDiskNode* UDirectoryNode::GetParent()
{
	return this->Parent;
}

FString UDirectoryNode::GetDiskNodeName()
{
	int DirectoryIndex;
	this->SaveGame->FindDirectoryIndex(this->DirectoryId, DirectoryIndex);
	return this->SaveGame->Directories[DirectoryIndex].Name;
}

TArray<UDiskNode*> UDirectoryNode::GetChildNodes()
{
	if (this->ChildrenDirty)
	{
		this->ChildrenDirty = false;
		this->Children.Empty();

		int DirectoryIndex;
		this->SaveGame->FindDirectoryIndex(this->DirectoryId, DirectoryIndex);

		for (int ChildDirectoryId : this->SaveGame->Directories[DirectoryIndex].Children)
		{
			UDirectoryNode* ChildNode = NewObject<UDirectoryNode>();
			ChildNode->LinkToDirectory(this, this->SaveGame, ChildDirectoryId);
			this->Children.Add(ChildNode);
		}

		for (int ChildFile : this->SaveGame->Directories[DirectoryIndex].Files)
		{
			UFileNode* fnode = NewObject<UFileNode>();
			fnode->LinkToFile(this, this->SaveGame, ChildFile);
			this->Children.Add(fnode);
		}
	}

	return this->Children;
}

void UDirectoryNode::LinkToDirectory(UDiskNode* InParent, URedemptionSaveGame* InSaveGame, int InDirectoryId)
{
	this->Parent = InParent;
	this->DirectoryId = InDirectoryId;
	this->SaveGame = InSaveGame;
}

UDirectoryNode* UDirectoryNode::MakeChildDirectory(FString InName)
{
	// refuse to create the directory if it already exists.
	if (this->GetChild(InName))
		return nullptr;

	// create the save data for the new dir
	FDirectoryEntry NewDir;
	NewDir.Name = InName;
	NewDir.Id = this->SaveGame->GetAvailableDirectoryId();

	// add the new dir to the save file
	this->SaveGame->Directories.Add(NewDir);

	// find this node's save data and add the new child.
	// this is so we can restore the directory tree next time the root node
	// is mounted.
	int MyIndex;
	this->SaveGame->FindDirectoryIndex(this->DirectoryId, MyIndex);
	this->SaveGame->Directories[MyIndex].Children.Add(NewDir.Id);

	// create the new node
	UDirectoryNode* NewNode = NewObject<UDirectoryNode>();
	NewNode->LinkToDirectory(this, this->SaveGame, NewDir.Id);

	// and link it to us.
	this->Children.Add(NewNode);
	return NewNode;
}

TArray<UDirectoryNode*> UDirectoryNode::GetChildDirectories()
{
	TArray<UDirectoryNode*> dirs;

	for (UDiskNode* node : this->Children)
	{
		UDirectoryNode* dir = Cast<UDirectoryNode>(node);
		if (dir)
			dirs.Add(dir);
	}
	
	return dirs;
}

TArray<UFileNode*> UDirectoryNode::GetChildFiles()
{
	TArray<UFileNode*> files;

	for (UDiskNode* node : this->Children)
	{
		UFileNode* file = Cast<UFileNode>(node);
		if (file)
			files.Add(file);
	}
	
	return files;

}

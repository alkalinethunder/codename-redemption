// Fill out your copyright notice in the Description page of Project Settings.


#include "FileNode.h"
#include "RedemptionSaveGame.h"
#include "DirectoryNode.h"
#include "FileData.h"

FFileData& UFileNode::GetFileData()
{
	int index;
	bool result = this->SaveGame->FindFileIndex(this->FileId, index);
	check (result);
	return this->SaveGame->Files[index];
}

FString UFileNode::GetTextContent()
{
	FFileData& data = this->GetFileData();

	if (data.FileType == EFileType::UserData)
	{
		return data.DataContent;
	}
	else
	{
		return ""; // TODO: peacenet-style random bitstream generation for asset files.
	}
}

void UFileNode::SetTextContent(FString InText)
{
	this->GetFileData().DataContent = InText;
}

FString UFileNode::GetDiskNodeName()
{
	return this->GetFileData().FileName;
}

TArray<UDiskNode*> UFileNode::GetChildNodes()
{
	return TArray<UDiskNode*>();
}

UDiskNode* UFileNode::GetParent()
{
	return this->ParentNode;
}

void UFileNode::LinkToFile(UDirectoryNode* InParent, URedemptionSaveGame* InSaveGame, int InFileId)
{
	check (InParent);
	check (InSaveGame);

	check (!this->ParentNode);
	check (!this->SaveGame);

	this->SaveGame = InSaveGame;
	this->ParentNode = InParent;
	this->FileId = InFileId;
}

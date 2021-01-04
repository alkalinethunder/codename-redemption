// Fill out your copyright notice in the Description page of Project Settings.


#include "DiskNode.h"

UDiskNode* UDiskNode::GetChild(FString InName)
{
	UDiskNode* result = nullptr;

	for (UDiskNode* Child : this->GetChildNodes())
	{
		if (Child->GetName() == InName)
		{
			result = Child;
			break;
		}
	}
	
	return result;
}

bool UDiskNode::DoesChildExist(FString InName)
{
	return this->GetChild(InName) != nullptr;
}

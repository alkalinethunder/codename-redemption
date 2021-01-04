// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DiskNode.generated.h"

/**
 * Internal representation of a Unix directory node.
 */
UCLASS(Abstract)
class REDEMPTION_API UDiskNode : public UObject
{
	GENERATED_BODY()

public:
	virtual UDiskNode* GetParent() PURE_VIRTUAL(UDiskNode::GetParent, return nullptr; );
	virtual FString GetDiskNodeName() PURE_VIRTUAL(UDiskNode::GetDiskNodeName, return ""; );
	virtual TArray<UDiskNode*> GetChildNodes() PURE_VIRTUAL(UDiskNode::GetChildNodes, return TArray<UDiskNode*>(); );

	UFUNCTION()
	UDiskNode* GetChild(FString InName);

	UFUNCTION()
	bool DoesChildExist(FString InName);
};

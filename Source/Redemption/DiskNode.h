// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DiskNode.generated.h"

/**
 * Internal representation of a Unix directory node.
 */
UCLASS()
class REDEMPTION_API UDiskNode : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	UDiskNode* Parent;

	UPROPERTY()
	FString Name;

	UPROPERTY()
	TArray<UDiskNode*> Children;
};

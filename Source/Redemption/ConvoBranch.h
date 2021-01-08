// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BranchActionInfo.h"
#include "ConvoChoice.h"
#include "ConvoBranch.generated.h"

/**
 * Represents a single branch in a Chat Conversation.
 */
USTRUCT(BlueprintType)
struct FConvoBranch
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FName Id;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<FBranchActionInfo> Actions;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<FConvoChoice> Choices;
};

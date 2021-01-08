// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ChatContact.h"
#include "BranchActionInfo.h"
#include "ConvoBranch.h"
#include "Conversation.generated.h"

/**
 * Represents the script of a player conversation.
 */
UCLASS(Blueprintable, BlueprintType)
class REDEMPTION_API UConversation : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Conversation")
	UChatContact* Contact = nullptr;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Conversation")
	FConvoBranch RootBranch;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Conversation")
	TArray<FConvoBranch> Branches;
};

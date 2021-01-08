// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Person.h"
#include "PersonalPronoun.h"
#include "ChatContact.generated.h"

/**
 * Represents a single person or group of people that the player
 * has as a contact in their Social Panel.
 */
UCLASS()
class REDEMPTION_API UChatContact : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Metadata")
	FText Name;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Conversation")
	TArray<UPerson*> ConversationMembers;

public:
	UFUNCTION(BlueprintPure)
	EPersonalPronoun GetPronoun();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChatAction.h"
#include "ConvoChoice.generated.h"

/**
 * Represents a choice the player can make during chat.
 */
USTRUCT(BlueprintType)
struct FConvoChoice
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FText DisplayText;

	UPROPERTY(BlueprintReadOnly, Instanced, EditAnywhere)
	UChatAction* ActionToPerform = nullptr;
};

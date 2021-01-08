// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChatAction.h"
#include "ChatContact.h"
#include "BranchActionInfo.generated.h"

/**
 * Represents a single Chat Action.
 */
USTRUCT(BlueprintType)
struct FBranchActionInfo
{
    GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UPerson* Person = nullptr;

	UPROPERTY(BlueprintReadOnly, Instanced, EditAnywhere)
	UChatAction* ActionToPerform = nullptr;
};

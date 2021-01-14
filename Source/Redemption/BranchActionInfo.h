// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BranchActionInfo.generated.h"

class UChatAction;

/**
 * Represents a single Chat Action.
 */
USTRUCT(BlueprintType)
struct FBranchActionInfo
{
    GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Instanced, EditAnywhere)
	UChatAction* ActionToPerform = nullptr;
};

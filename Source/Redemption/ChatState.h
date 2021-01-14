// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChatState.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EChatState : uint8
{
    Playing,
	AwaitingChoices,
	ExecutingChoice
};

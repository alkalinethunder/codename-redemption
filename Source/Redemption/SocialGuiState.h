// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SocialGuiState.generated.h"

/**
 * Represents the last state of the Social Panel in the GUI.
 */
UENUM(BlueprintType)
enum class ESocialGuiState : uint8
{
    Feed,
	Contacts,
	Messages
};

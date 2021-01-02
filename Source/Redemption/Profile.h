// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveSlot.h"
#include "Profile.generated.h"

/**
 * Contains global settings and the master list of save files.
 */
UCLASS()
class REDEMPTION_API UProfile : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "Saves")
	TArray<FSaveSlot> SaveGameSlots;

	UPROPERTY(BlueprintReadOnly, Category = "Saves")
	int LastSlotIndex;
};

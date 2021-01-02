#pragma once

#include "CoreMinimal.h"
#include "SaveSlot.generated.h"

USTRUCT(BlueprintType)
struct FSaveSlot
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	FString SlotName;

	UPROPERTY(BlueprintReadOnly)
	FString LastMission;

	UPROPERTY(BlueprintReadOnly)
	FString GameModeName;

	UPROPERTY(BlueprintReadOnly)
	FDateTime Created;

	UPROPERTY(BlueprintReadOnly)
	FDateTime LastPlayed;
};
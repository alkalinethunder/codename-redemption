#pragma once

#include "CoreMinimal.h"
#include "SpawnFlags.generated.h"

USTRUCT(BlueprintType)
struct FSpawnFlags
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool bIsLootable = false;
};
#pragma once

#include "CoreMinimal.h"
#include "Difficulty.generated.h"

UENUM(BlueprintType)
enum class EDifficulty : uint8
{
	Easy,
	Medium,
	Hard,
	Fucked,

	nUM_EDifficulty UMETA(Hidden)
};
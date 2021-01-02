#pragma once

#include "CoreMinimal.h"
#include "ProgressionLevel.generated.h"

USTRUCT(BlueprintType)
struct FProgressionLevel
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FString LevelName;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int ExperienceNeeded;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int UpgradePointsToGive = 5;
};

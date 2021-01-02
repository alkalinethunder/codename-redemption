#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ProgressionLevel.h"
#include "ProgressionLevelsListAsset.generated.h"

UCLASS(Blueprintable, BlueprintType)
class UProgressionLevelsListAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Progression Levels List")
	FString StartingLevelName;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Progression Levels List")
	TArray<FProgressionLevel> Levels;
};

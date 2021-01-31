#pragma once

#include "CoreMinimal.h"
#include "NetRoute.generated.h"

USTRUCT(BlueprintType)
struct REDEMPTION_API FNetRoute
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int Start;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int End;
};
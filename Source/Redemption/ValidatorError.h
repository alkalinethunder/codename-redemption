#pragma once

#include "CoreMinimal.h"
#include "ValidatorError.generated.h"

USTRUCT(BlueprintType)
struct REDEMPTION_API FValidatorError
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool HasError = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText ErrorText;
};
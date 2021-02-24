#pragma once

#include "CoreMinimal.h"
#include "User.generated.h"

USTRUCT(BlueprintType)
struct REDEMPTION_API FUser
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	int UserId;

	UPROPERTY(BlueprintReadOnly)
	FString UserName;
};
#pragma once

#include "CoreMinimal.h"
#include "HackableType.h"
#include "Difficulty.h"
#include "Hackable.generated.h"

USTRUCT(BlueprintType)
struct REDEMPTION_API FHackable
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int Port;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FString Name;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool bIsHacked = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool bHasTrace = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool bIsFirewalled = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	EHackableType HackableType;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	EDifficulty Difficulty;
};
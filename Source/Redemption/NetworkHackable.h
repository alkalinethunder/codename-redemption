#pragma once

#include "CoreMinimal.h"
#include "NetworkHackable.generated.h"

USTRUCT(BlueprintType)
struct REDEMPTION_API FNetworkHackable
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int DeviceId;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int HackableId;
};

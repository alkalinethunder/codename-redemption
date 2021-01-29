#pragma once

#include "CoreMinimal.h"

#include "DeviceType.h"
#include "Difficulty.h"
#include "Engine/DataAsset.h"
#include "SpecialDeviceAsset.generated.h"

UCLASS(BlueprintType)
class REDEMPTION_API USpecialDeviceAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Metadata")
	FText Name;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Metadata")
	FString HostName;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Device")
	EDeviceType DeviceType;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Device")
	EDifficulty Difficulty;
};
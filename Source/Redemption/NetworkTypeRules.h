#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "NetworkType.h"
#include "HackableType.h"
#include "DeviceType.h"
#include "NetworkTypeRules.generated.h"

UCLASS(BlueprintType)
class REDEMPTION_API UNetworkTypeRules : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Network Type")
	ENetworkType NetworkType;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Generation Requirements")
	TArray<EDeviceType> RequiredDevices;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Generation Requirements")
	TArray<EHackableType> Hackables;
};
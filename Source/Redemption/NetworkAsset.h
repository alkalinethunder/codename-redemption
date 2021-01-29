#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "NetworkType.h"
#include "Difficulty.h"
#include "SpecialDeviceAsset.h"
#include "NetworkAsset.generated.h"

UCLASS(BlueprintType)
class REDEMPTION_API UNetworkAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Metadata")
	FText Name;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Metadata")
	FString HostName;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Network Type")
	ENetworkType NetworkType;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Network Type")
	EDifficulty Difficulty;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Special")
	TArray<USpecialDeviceAsset*> SpecialDevices;
	
};
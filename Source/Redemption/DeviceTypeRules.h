#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DeviceType.h"
#include "HackableType.h"
#include "DeviceTypeRules.generated.h"

UCLASS(BlueprintType)
class REDEMPTION_API UDeviceTypeRules : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Device Type Rules")
	EDeviceType DeviceType;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Hackables")
	TArray<EHackableType> Hackables;
};
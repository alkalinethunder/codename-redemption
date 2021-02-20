// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Device.h"
#include "Network.h"
#include "GameStructUtils.generated.h"

class URedemptionGameInstance;

/**
 * Class containing functions related to handling gameplay structures.
 */
UCLASS(BlueprintType)
class REDEMPTION_API UGameStructUtils : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	static bool IsDeviceHacked(const FDevice& InDevice);

	UFUNCTION(BlueprintPure)
	static int DefaultPort(EHackableType HackableType);
	
	UFUNCTION()
	static void DeleteUnhackedHackables(FDevice& InDevice);

	UFUNCTION()
	static bool NetworkHasRouter(URedemptionGameInstance* GameInstance, const FNetwork& InNetwork);
};

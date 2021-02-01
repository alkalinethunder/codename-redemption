// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "NetworkNode.h"
#include "UObject/Object.h"
#include "DeviceNode.generated.h"

UCLASS(BlueprintType)
class REDEMPTION_API UDeviceNode : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UNetworkNode* NetworkNode;

	UPROPERTY()
	int DeviceId;
	
public:
	UFUNCTION()
	void Init(UNetworkNode* InNetwork, int InDeviceId);
};

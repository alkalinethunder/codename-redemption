// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DeviceType.h"
#include "Device.generated.h"

USTRUCT(BlueprintType)
struct FDevice
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int Id;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FString AssetId;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int DiskRoot;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FString LocalIP;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FString Hostname;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FString Name;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	EDeviceType DeviceType;
};

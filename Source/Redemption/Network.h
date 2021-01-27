// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Network.generated.h"

USTRUCT(BlueprintType)
struct FNetwork
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FString Name;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FString HostName;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FString IPAddress;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FString LocalSubnet;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<int> Devices;
};

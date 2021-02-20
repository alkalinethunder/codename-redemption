// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Network.h"
#include "NetworkNode.generated.h"

class UNetworkManager;
class UDeviceNode;

UCLASS(BlueprintType)
class REDEMPTION_API UNetworkNode : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TArray<UDeviceNode*> Devices;
	
	UPROPERTY()
	TArray<UNetworkNode*> Connections;
	
	UPROPERTY()
	UNetworkManager* NetworkManager;

	UPROPERTY()
	int NetworkId;

private:
	UFUNCTION()
	FNetwork& GetNetwork();
	
public:
	UFUNCTION()
	void Init(UNetworkManager* InNetManager, int InNetId);

	UFUNCTION()
	void AddConnection(UNetworkNode* InNode);

	UFUNCTION()
	bool ResolveLocalDevice(FString InHost, int& OutDeviceIndex);
	
public:
	UFUNCTION(BlueprintCallable)
    TArray<UNetworkNode*> TraceRoute(UNetworkNode* InDestination);

	UFUNCTION(BlueprintType)
	EDifficulty GetDifficulty();
	
	UFUNCTION(BlueprintPure)
	int GetNetworkId();

	UFUNCTION(BlueprintPure)
	FString GetNetworkName();

	UFUNCTION(BlueprintPure)
    FString GetHostName();

	UFUNCTION(BlueprintPure)
    FString GetIPAddress();

public:
	UFUNCTION()
	void GetHackables(TArray<FHackable>& OutHackables);
};

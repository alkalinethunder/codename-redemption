// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Network.h"
#include "NetworkNode.generated.h"

class UNetworkManager;

UCLASS(BlueprintType)
class REDEMPTION_API UNetworkNode : public UObject
{
	GENERATED_BODY()

private:
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
	TArray<UNetworkNode*> TraceRoute(UNetworkNode* InDestination);
	
public:
	UFUNCTION(BlueprintPure)
	int GetNetworkId();

	UFUNCTION(BlueprintPure)
	FString GetNetworkName();

	UFUNCTION(BlueprintPure)
    FString GetHostName();

	UFUNCTION(BlueprintPure)
    FString GetIPAddress();

};

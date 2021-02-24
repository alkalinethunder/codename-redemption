// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "NetworkNode.h"
#include "Hackable.h"
#include "HackSession.h"
#include "NetworkManager.generated.h"

class UUserContext;
class ARedemptionGameState;

UCLASS(BlueprintType)
class REDEMPTION_API UNetworkManager : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY()
	ARedemptionGameState* GameState;

	UPROPERTY()
	TArray<UNetworkNode*> Nodes;

private:
	UFUNCTION()
	UNetworkNode* MapNetwork(FString InHost);
	
public:
	UFUNCTION()
	void Init(ARedemptionGameState* InGameState);

	UFUNCTION()
	ARedemptionGameState* GetGameState();

public:
	UFUNCTION()
	UHackSession* BeginHack(UUserContext* InUserContext, FString InTargetHost);

public:
	UFUNCTION(BlueprintCallable)
	bool GetHackables(UNetworkNode* InNetwork, FString InHost, TArray<FHackable>& OutHackables);
	
	UFUNCTION(BlueprintPure)
	UNetworkNode* GetNetworkNode(int InNetworkId);

	UFUNCTION(BlueprintPure)
	bool ResolveNetworkAddress(FString IPAddress, UNetworkNode*& OutNetwork);
};

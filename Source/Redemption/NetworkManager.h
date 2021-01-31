// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "NetworkNode.h"
#include "NetworkManager.generated.h"

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
	
public:
	UFUNCTION()
	void Init(ARedemptionGameState* InGameState);

	UFUNCTION()
	ARedemptionGameState* GetGameState();

public:
	UFUNCTION(BlueprintPure)
	UNetworkNode* GetNetworkNode(int InNetworkId);
};

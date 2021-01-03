// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "RedemptionGameState.generated.h"

class UUpgradeAsset;

UCLASS(BlueprintType)
class REDEMPTION_API ARedemptionGameState : public AGameStateBase
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TArray<UUpgradeAsset*> Upgrades;

public:
	// Sets default values for this actor's properties
	ARedemptionGameState();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
	TArray<UUpgradeAsset*> GetAllUpgrades();
};

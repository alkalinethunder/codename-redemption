#pragma once

#include "CoreMinimal.h"
#include "LatentGameplayTask.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLatentCompletion);

class ARedemptionGameState;

UCLASS()
class REDEMPTION_API ULatentGameplayTask : public UObject
{
	friend ARedemptionGameState; // I've run out of Pokemon episodes with Ritchie in them that have suitable names to use in these "friend whatever" clauses so instead I've wrote this text.
	
	GENERATED_BODY()

private:
	UPROPERTY()
	float TimeLeft;

	UPROPERTY()
	bool bBegun = false;
	
public:
	UPROPERTY()
	FLatentCompletion Done;

public:
	UFUNCTION()
	void Begin();
};
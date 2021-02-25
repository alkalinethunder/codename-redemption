#pragma once

#include "CoreMinimal.h"
#include "HackTrace.generated.h"

class UHackSession;
class UHackableinfo;
class ARedemptionGameState;

UCLASS(BlueprintType)
class REDEMPTION_API UHackTrace : public UObject
{
	friend ARedemptionGameState; // Friends and foes alike.
	
	GENERATED_BODY()

private:
	UPROPERTY()
	float TraceTimeLeft;
	
	UPROPERTY()
	UHackSession* HackSession;

	UPROPERTY()
	UHackableinfo* Hackable;

	UPROPERTY()
	ARedemptionGameState* GameState;

private:
	UFUNCTION()
	void BindTrace(ARedemptionGameState* InGameState, UHackSession* InHack, UHackableinfo* InHackable);
};
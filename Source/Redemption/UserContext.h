#pragma once

#include "CoreMinimal.h"
#include "UserContext.generated.h"

class ARedemptionGameState;

UCLASS(BlueprintType)
class REDEMPTION_API UUserContext : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY()
	int DeviceId;

	UPROPERTY()
	int NetId;

	UPROPERTY()
	ARedemptionGameState* GameState;

public:
	UFUNCTION()
	void BindToDevice(int InNetworkId, int InDeviceId, ARedemptionGameState* InGameState);
};
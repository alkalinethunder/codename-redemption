#pragma once

#include "CoreMinimal.h"
#include "Device.h"
#include "Network.h"
#include "User.h"
#include "UserContext.generated.h"

class ARedemptionGameState;

UCLASS(BlueprintType)
class REDEMPTION_API UUserContext : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY()
	int UserId = 0; // 0 = root
	
	UPROPERTY()
	int DeviceId;

	UPROPERTY()
	int NetId;

	UPROPERTY()
	ARedemptionGameState* GameState;

public:
	UFUNCTION()
	void BindToDevice(int InNetworkId, int InDeviceId, ARedemptionGameState* InGameState);

	UFUNCTION()
	bool SetUserId(int InUserId);
	
	UFUNCTION()
	FNetwork& GetNetwork();

	UFUNCTION()
	FDevice& GetDevice();
	
public:
	UFUNCTION(BlueprintPure)
	TArray<FUser> GetUsers();
	
	UFUNCTION(BlueprintPure)
	bool IsSuperUser();

	UFUNCTION(BlueprintPure)
	FString GetUsername();

	UFUNCTION(BlueprintPure)
	FString GetHostName();

	UFUNCTION(BlueprintPure)
	FString GetLocalIP();

	UFUNCTION(BlueprintPure)
	FString GetPublicIP();
};
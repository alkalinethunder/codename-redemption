#pragma once

#include "CoreMinimal.h"
#include "Hackable.h"
#include "NetworkHackable.h"
#include "Device.h"
#include "HackableInfo.generated.h"

class UHackSession;

UCLASS(BlueprintType)
class REDEMPTION_API UHackableinfo : public UObject
{
	friend UHackSession; // Another friend in deed...
	
	GENERATED_BODY()

private:
	UPROPERTY()
	int HackableId;

	UPROPERTY()
	int DeviceId;

	UPROPERTY()
	UHackSession* HackSession;

private:
	UFUNCTION()
	void BindHackable(UHackSession* InHackSession, int InDevice, int InHackable);

public:
	UFUNCTION()
	FHackable& GetHackable();

	UFUNCTION()
	FDevice& GetDevice();

	UFUNCTION()
	FString GetDeviceAddress();

	UFUNCTION()
	FString GetDeviceName();

	UFUNCTION()
	int GetPort();

	UFUNCTION()
	FString GetHackableId();

	UFUNCTION()
	FString GetHackableName();

	UFUNCTION()
	bool GetHasTrace();

	UFUNCTION()
	bool GetHasFirewall();

	UFUNCTION()
	float GetTraceTimeout();
};
#pragma once

#include "CoreMinimal.h"
#include "DeviceType.generated.h"

UENUM(BlueprintType)
enum class EDeviceType : uint8
{
	Player UMETA(Hidden),
	Router,
	Workstation,
	NetServer,
	Database,
	TrafficMonitor,
	Firewall,
	FileServer,
	Phone,
	SmartWatch,
	Television,
	CarInfotainment,
	CellTower,
	AutomatedTeller,
	LotteryTerminal,

	NUM_DeviceType UMETA(Hidden),
};
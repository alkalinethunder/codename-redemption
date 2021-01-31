// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStructUtils.h"

#include "RedemptionGameInstance.h"

bool UGameStructUtils::IsDeviceHacked(const FDevice& InDevice)
{
	bool result = false;

	for (const FHackable& hackable : InDevice.Hackables)
	{
		if (hackable.bIsHacked)
		{
			result = true;
			break;
		}
	}
	
	return result;
}

void UGameStructUtils::DeleteUnhackedHackables(FDevice& InDevice)
{
	TArray<int> toDelete;
	for (int i = 0; i < InDevice.Hackables.Num(); i++)
	{
		if (!InDevice.Hackables[i].bIsHacked)
			toDelete.Add(i);
	}

	while (toDelete.Num())
	{
		int last = toDelete.Num() - 1;
		int riolu = toDelete[last];
		InDevice.Hackables.RemoveAt(riolu);
		toDelete.RemoveAt(last);
	}
}

bool UGameStructUtils::NetworkHasRouter(URedemptionGameInstance* GameInstance, const FNetwork& InNetwork)
{
	bool result = false;
	for (FDevice& dev : GameInstance->GetSaveGame()->Devices)
	{
		if (InNetwork.Devices.Contains(dev.Id) && dev.DeviceType == EDeviceType::Router)
		{
			result = true;
			break;
		}
	}
	return result;
}

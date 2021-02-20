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

int UGameStructUtils::DefaultPort(EHackableType HackableType)
{
	switch (HackableType)
	{
		case EHackableType::Cast:
			return 9080; // apparently my new monitor has this port open on the LAN...nmap says it's "glrpc"
		case EHackableType::Chat:
			return 6667;
		case EHackableType::Ftp:
			return 21;
		case EHackableType::Http:
			return 80;
		case EHackableType::Https:
			return 443;
		case EHackableType::Sql:
			return 3800;
		case EHackableType::Ssh:
			return 22;
		case EHackableType::Voip:
			return 420;
		case EHackableType::RemoteDesktop:
			return 3389;
		default:
			return 0;
	}
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

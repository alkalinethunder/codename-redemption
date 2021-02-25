#include "HackableInfo.h"

#include "GameStructUtils.h"
#include "HackSession.h"
#include "RedemptionGameInstance.h"
#include "RedemptionGameState.h"

void UHackableinfo::BindHackable(UHackSession* InHackSession, int InDevice, int InHackable)
{
	check (InHackSession);
	this->HackSession = InHackSession;
	this->DeviceId = InDevice;
	this->HackableId = InHackable;
}

FHackable& UHackableinfo::GetHackable()
{
	return this->GetDevice().Hackables[this->HackableId];
}

FDevice& UHackableinfo::GetDevice()
{
	int index = this->HackSession->GetGameState()->GetGameInstance()->GetSaveGame()->MapDevice(this->DeviceId);
	return this->HackSession->GetGameState()->GetGameInstance()->GetSaveGame()->Devices[index];
}

FString UHackableinfo::GetDeviceAddress()
{
	return this->HackSession->GetNetwork().LocalSubnet + "." + this->GetDevice().LocalIP;
}

FString UHackableinfo::GetDeviceName()
{
	FString name = this->GetDevice().Name;
	if (name.TrimEnd().Len())
	{
		return name;
	}
	else
	{
		return this->GetDeviceAddress();
	}
}

int UHackableinfo::GetPort()
{
	return this->GetHackable().Port;
}

FString UHackableinfo::GetHackableId()
{
	return UGameStructUtils::GetHackableIdentifier(this->GetHackable().HackableType);
}

FString UHackableinfo::GetHackableName()
{
	FString name = this->GetHackable().Name;
	if (name.TrimEnd().Len() && name != "<unknown>")
	{
		return name;
	}
	else
	{
		return this->GetHackableId();
	}
}

bool UHackableinfo::GetHasTrace()
{
	return this->GetHackable().bHasTrace;
}

bool UHackableinfo::GetHasFirewall()
{
	return this->GetHackable().bIsFirewalled;
}

float UHackableinfo::GetTraceTimeout()
{
	float totalTraceTime = this->HackSession->GetGameState()->GetGameMode()->TraceTimeout;

	switch (this->GetHackable().Difficulty)
	{
		case EDifficulty::Easy:
			return totalTraceTime;
		case EDifficulty::Fucked:
			return totalTraceTime / 4;
		case EDifficulty::Hard:
			return totalTraceTime / 3;
		case EDifficulty::Medium:
			return totalTraceTime / 2;
	}

	return totalTraceTime;
}

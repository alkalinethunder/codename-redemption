#include "UserContext.h"

#include "RedemptionGameInstance.h"
#include "RedemptionGameState.h"

void UUserContext::BindToDevice(int InNetworkId, int InDeviceId, ARedemptionGameState* InGameState)
{
	check(InGameState);
	check (!this->GameState);

	this->GameState = InGameState;
	this->NetId = InNetworkId;
	this->DeviceId = InDeviceId;
}

FNetwork& UUserContext::GetNetwork()
{
	int index =	this->GameState->GetGameInstance()->GetSaveGame()->MapNetwork(this->NetId);
	return this->GameState->GetGameInstance()->GetSaveGame()->Networks[index];
}

FDevice& UUserContext::GetDevice()
{
	int index =	this->GameState->GetGameInstance()->GetSaveGame()->MapDevice(this->NetId);
	return this->GameState->GetGameInstance()->GetSaveGame()->Devices[index];
}

bool UUserContext::IsSuperUser()
{
	return this->UserId == 0;
}

FString UUserContext::GetUsername()
{
	return "root"; // TODO.
}

FString UUserContext::GetHostName()
{
	return this->GetDevice().Hostname;
}

FString UUserContext::GetLocalIP()
{
	return this->GetNetwork().LocalSubnet + "." + this->GetDevice().LocalIP;
}

FString UUserContext::GetPublicIP()
{
	return this->GetNetwork().IPAddress;
}

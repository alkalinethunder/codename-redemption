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

bool UUserContext::SetUserId(int InUserId)
{
	if (this->GetUsers().Num() > InUserId && InUserId >= 0)
	{
		this->UserId = InUserId;
		return true;
	}

	return false;
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

TArray<FUser> UUserContext::GetUsers()
{
	TArray<FUser> result;

	FUser root;
	root.UserId = 0;
	root.UserName = "root";

	result.Add(root);

	int i = 1;
	for (FString username : this->GetDevice().Users)
	{
		FUser u;
		u.UserId = i;
		u.UserName = username;
		result.Add(u);
		i++;
	}
	
	return result;
}

bool UUserContext::IsSuperUser()
{
	return this->UserId == 0;
}

FString UUserContext::GetUsername()
{
	TArray<FUser> users = this->GetUsers();
	return users[this->UserId].UserName;
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

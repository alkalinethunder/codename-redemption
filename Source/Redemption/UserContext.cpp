#include "UserContext.h"
#include "RedemptionGameState.h"

void UUserContext::BindToDevice(int InNetworkId, int InDeviceId, ARedemptionGameState* InGameState)
{
	check(InGameState);
	check (!this->GameState);

	this->GameState = InGameState;
	this->NetId = InNetworkId;
	this->DeviceId = InDeviceId;
}
#include "HackSession.h"
#include "NetworkManager.h"

void UHackSession::SetGameState(ARedemptionGameState* InGameState)
{
	this->GameState = InGameState;
}

void UHackSession::SetUserContext(UUserContext* InUserContext)
{
	this->UserContext = InUserContext;
}

void UHackSession::SetHopsCount(int InHopsCount)
{
	this->HopsCount = InHopsCount;
}

void UHackSession::SetSourceNetwork(UNetworkNode* InNetwork)
{
	this->SourceNetwork = InNetwork;
}

void UHackSession::SetDestinationNetwork(UNetworkNode* InNetwork)
{
	this->DestinationNetwork = InNetwork;
}

void UHackSession::SetDestinationAddress(FString InNetworkAddress)
{
	this->DestinationAddress = InNetworkAddress;
}

#include "HackSession.h"
#include "NetworkManager.h"
#include "RedemptionGameState.h"

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

void UHackSession::BeginTrace(UHackableinfo* InTraceSource)
{
	check (InTraceSource);
	this->GetGameState()->BeginTrace(this, InTraceSource);
}

FNetwork& UHackSession::GetNetwork()
{
	return this->DestinationNetwork->GetNetwork();
}

TArray<UHackableinfo*> UHackSession::GetHackables()
{
	if (!this->bAnalyzedHackables)
	{
		for (FNetworkHackable hackable : this->DestinationNetwork->GetNetHackables())
		{
			UHackableinfo* hInfo = NewObject<UHackableinfo>();
			hInfo->BindHackable(this, hackable.DeviceId, hackable.HackableId);
			this->Hackables.Add(hInfo);
		}
		
		this->bAnalyzedHackables = true;
	}
	
	return this->Hackables;
}

ARedemptionGameState* UHackSession::GetGameState()
{
	return this->GameState;
}

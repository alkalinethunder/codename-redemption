#include "HackTrace.h"
#include "HackableInfo.h"
#include "HackSession.h"
#include "RedemptionGameState.h"

void UHackTrace::BindTrace(ARedemptionGameState* InGameState, UHackSession* InHack, UHackableinfo* InHackable)
{
	check (InGameState);
	check (InHack);
	check (InHackable);

	this->GameState = InGameState;
	this->HackSession = InHack;
	this->Hackable = InHackable;

	this->TraceTimeLeft = InHackable->GetTraceTimeout();
}

float UHackTrace::GetTimeLeft()
{
	return this->TraceTimeLeft;
}

FString UHackTrace::GetTraceName()
{
	return this->HackSession->GetNetwork().Name;
}

FString UHackTrace::GetTraceAddress()
{
	return this->HackSession->GetNetwork().IPAddress;
}

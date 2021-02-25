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

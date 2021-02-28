#include "GameplayAction.h"
#include "RedemptionGameState.h"

void UGameplayAction::NativeActionRun()
{
	this->ActionRun();
}

ARedemptionGameState* UGameplayAction::GetGameState()
{
	return this->GameState;
}

void UGameplayAction::Run(ARedemptionGameState* InGameState)
{
	check (InGameState);

	this->GameState = InGameState;

	this->NativeActionRun();
}

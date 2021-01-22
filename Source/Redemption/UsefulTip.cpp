// Fill out your copyright notice in the Description page of Project Settings.


#include "UsefulTip.h"
#include "RedemptionPlayerController.h"
#include "RedemptionPlayerState.h"

FText UUsefulTip::GetTipText(ARedemptionPlayerController* InPlayerController)
{
	if (this->RequiredUpgrade)
	{
		ARedemptionPlayerState* playerState = Cast<ARedemptionPlayerState>(InPlayerController->PlayerState);
		if (this->RequiredUpgrade->IsUnlocked(playerState))
		{
			return this->TipTextAfterUpgrade;
		}
	}

	return this->TipText;
}

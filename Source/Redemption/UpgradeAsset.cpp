// Fill out your copyright notice in the Description page of Project Settings.


#include "UpgradeAsset.h"
#include "RedemptionPlayerState.h"
#include "RedemptionSaveGame.h"

bool UUpgradeAsset::IsUnlocked(ARedemptionPlayerState* InPlayerState)
{
	return InPlayerState->GetSaveGame()->UnlockedUpgrades.Contains(this->GetFName());
}

bool UUpgradeAsset::IsAvailable(ARedemptionPlayerState* InPlayerState)
{
	bool result = true;

	// not available if we're unlocked already
	if (this->IsUnlocked(InPlayerState))
	{
		result = false;
	}
	else
	{
		// check current level
		result = InPlayerState->GetLevel() >= this->RequiredSkillLevel;

		// check upgrade points
		result = InPlayerState->GetUpgradePoints() >= this->RequiredUpgradePoints;

		// and now, check requirements
		for (UUpgradeAsset* requirement : this->RequiredUpgrades)
		{
			if (!requirement->IsUnlocked(InPlayerState))
			{
				result = false;
				break;
			}
		}
	}
	
	return result;
}

bool UUpgradeAsset::TryUnlock(ARedemptionPlayerState* InPlayerState)
{
	bool result = true;

	if (this->IsUnlocked(InPlayerState) || !this->IsAvailable(InPlayerState))
	{
		result = false;
	}
	else
	{
		// mark the upgrade as unlocked.
		InPlayerState->GetSaveGame()->UnlockedUpgrades.Add(this->GetFName());
		
		// subtract upgrade points
		InPlayerState->RemoveUpgradePoints(this->RequiredUpgradePoints);

		result = true;
	}

	return result;
}

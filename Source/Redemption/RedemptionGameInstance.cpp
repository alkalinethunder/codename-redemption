// Fill out your copyright notice in the Description page of Project Settings.


#include "RedemptionGameInstance.h"

#include "RedemptionGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void URedemptionGameInstance::SaveProfile()
{
	UGameplayStatics::SaveGameToSlot(this->Profile, this->ProfileSlotName, 0);
}

void URedemptionGameInstance::Init()
{
	// Pick a slot name.
	this->ProfileSlotName = "profile";

	// Check if it exists.
	if (UGameplayStatics::DoesSaveGameExist(this->ProfileSlotName, 0))
	{
		// Load it.
		this->Profile = Cast<UProfile>(UGameplayStatics::LoadGameFromSlot(this->ProfileSlotName, 0));
	}
	else
	{
		// Create it.
		this->Profile = NewObject<UProfile>();
	}
}

void URedemptionGameInstance::Shutdown()
{
	// end the game session, if any
	this->EndSession();
	
	// Save the profile.
	this->SaveProfile();

	// and unload it
	this->Profile = nullptr;
}

bool URedemptionGameInstance::DoesAnySlotExist()
{
	return this->Profile && this->Profile->SaveGameSlots.Num() > 0;
}

bool URedemptionGameInstance::GetLastPlayedGame(FSaveSlot& OutSlot, int& OutSlotIndex)
{
	if (this->DoesAnySlotExist() && this->Profile->LastSlotIndex >= 0)
	{
		OutSlotIndex = this->Profile->LastSlotIndex;
		OutSlot = this->Profile->SaveGameSlots[this->Profile->LastSlotIndex];
		return true;
	}
	else
	{
		return false;
	}
}

bool URedemptionGameInstance::IsPlayerNameAvailable(FString InPlayerName)
{
	if (this->DoesAnySlotExist())
	{
		for (FSaveSlot& Slot : this->Profile->SaveGameSlots)
		{
			if (Slot.SlotName == InPlayerName)
			{
				return false;
			}
		}

		return true;
	}
	else
	{
		return true;
	}
}

void URedemptionGameInstance::CreateGameSlot(FString InPlayerName)
{
	// crash the game if people are idiots.
	check(this->Profile);
	check(this->IsPlayerNameAvailable(InPlayerName));

	// create the slot info.
	FSaveSlot NewSlot;
	NewSlot.Created = FDateTime::Now();
	NewSlot.SlotName = InPlayerName;

	// Set our current slot index and store it as the last played slot.
	this->CurrentGameSlot = this->Profile->SaveGameSlots.Num();
	this->Profile->LastSlotIndex = this->CurrentGameSlot;
	
	// add the slot to the save list
	this->Profile->SaveGameSlots.Add(NewSlot);

	// and finally, save the profile.
	this->SaveProfile();
}

bool URedemptionGameInstance::ContinueGame(int SlotIndex)
{
	if (this->CurrentGameSlot >= 0)
	{
		return false;
	}
	
	if (this->DoesAnySlotExist())
	{
		if (SlotIndex >= 0 && SlotIndex < this->Profile->SaveGameSlots.Num())
		{
			this->CurrentGameSlot = SlotIndex;
			return true;
		}
	}

	return false;
}

FSaveSlot& URedemptionGameInstance::GetSlotInfo()
{
	return this->Profile->SaveGameSlots[this->CurrentGameSlot];
}

void URedemptionGameInstance::StartSession(ARedemptionGameModeBase* GameMode)
{
	if (this->CurrentGameSlot > -1)
	{
		if (UGameplayStatics::DoesSaveGameExist(this->GetSlotInfo().SlotName, 0))
		{
			this->CurrentGameSave = Cast<URedemptionSaveGame>(UGameplayStatics::LoadGameFromSlot(this->GetSlotInfo().SlotName, 0));
		}
		else
		{
			this->CurrentGameSave = NewObject<URedemptionSaveGame>();

			// set default values.
			this->CurrentGameSave->DesktopWallpaper = GameMode->DefaultWallpaper;
			this->CurrentGameSave->Experience = GameMode->StartingExperiencePoints;
			this->CurrentGameSave->UpgradePoints = GameMode->StartingUpgradePoints;
		}

		this->GetSlotInfo().LastPlayed = FDateTime::Now();
		this->SaveProfile();

		this->SaveGame();
	}
}

void URedemptionGameInstance::EndSession()
{
	if (this->CurrentGameSave)
	{
		this->SaveGame();
		this->CurrentGameSave = nullptr;
		this->Profile->LastSlotIndex = this->CurrentGameSlot;
		this->CurrentGameSlot = -1;
		this->SaveProfile();
	}
}

void URedemptionGameInstance::SaveGame()
{
	UGameplayStatics::SaveGameToSlot(this->CurrentGameSave, this->GetSlotInfo().SlotName, 0);
}

URedemptionSaveGame* URedemptionGameInstance::GetSaveGame()
{
	return this->CurrentGameSave;
}

void URedemptionGameInstance::AddXP(int Amount)
{
	this->GetSaveGame()->Experience += FMath::Abs(Amount);
	this->OnExperienceAdded.Broadcast();
}

void URedemptionGameInstance::AddUpgradePoints(int Amount)
{
	this->CurrentGameSave->UpgradePoints += FMath::Abs(Amount);
}

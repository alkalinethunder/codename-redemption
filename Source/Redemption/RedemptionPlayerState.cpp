﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "RedemptionPlayerState.h"
#include "RedemptionGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "RedemptionGameModeBase.h"
#include "RedemptionSaveGame.h"

URedemptionSaveGame* ARedemptionPlayerState::GetSaveGame()
{
	return this->GameInstance->GetSaveGame();
}

bool ARedemptionPlayerState::RemoveUpgradePoints(int Amount)
{
	if (this->GetUpgradePoints() >= Amount)
	{
		this->GetSaveGame()->UpgradePoints -= Amount;
		this->GameInstance->SaveGame();
		return true;
	}
	else
	{
		return false;
	}
}

// Sets default values
ARedemptionPlayerState::ARedemptionPlayerState()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARedemptionPlayerState::BeginPlay()
{
	Super::BeginPlay();

	this->GameInstance = Cast<URedemptionGameInstance>(this->GetGameInstance());
	this->GameMode = Cast<ARedemptionGameModeBase>(UGameplayStatics::GetGameMode(this));
	
	this->GameInstance->OnExperienceAdded.AddUniqueDynamic(this, &ARedemptionPlayerState::UpdateSkillState);
	
	this->UpdateSkillState();
}

// Called every frame
void ARedemptionPlayerState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARedemptionPlayerState::UpdateSkillState()
{
	// set our total XP internally
	this->TotalXP = this->GameInstance->GetSaveGame()->Experience;

	// This is a running total, we'll use it to compute the level.
	int total = this->TotalXP;

	// this is the level we're on.
	int level = 1;
	int start = 0;
	int pointsToGive = 0;
	FString levelName = this->GameMode->LevelsList->StartingLevelName;

	// loop through all of the levels in the game mode
	for(FProgressionLevel& levelData : this->GameMode->LevelsList->Levels)
	{
		if (total < levelData.ExperienceNeeded)
		{
			this->LevelStartXP = start;
			this->XPNeededForNextLevel = start + levelData.ExperienceNeeded;
			break;
		}

		start += levelData.ExperienceNeeded;
		level++;
		levelName = levelData.LevelName;
		total -= levelData.ExperienceNeeded;

		if (this->GameInstance->GetSaveGame()->Level < level)
		{
			pointsToGive += levelData.UpgradePointsToGive;
			
			this->GameInstance->GetSaveGame()->Level = level;
			this->OnLevelUp.Broadcast(levelData);
		}
	}

	// add upgrade points if any.
	if (pointsToGive > 0)
	{
		this->GameInstance->AddUpgradePoints(pointsToGive);
	}
	
	// set the level state
	this->Level = level;
	this->LevelName = levelName;
}

FString ARedemptionPlayerState::GetLevelName()
{
	return this->LevelName;
}

float ARedemptionPlayerState::GetLevelPercentage()
{
	float start = (float) this->LevelStartXP;
	float current = (float) this->TotalXP;
	float end = (float) this->XPNeededForNextLevel;

	float x = current - start;
	float y = end - start;
	
	return FMath::Clamp(x / y, 0.f, 1.f);
}

int ARedemptionPlayerState::GetUpgradePoints()
{
	return this->GameInstance->GetSaveGame()->UpgradePoints;
}

int ARedemptionPlayerState::GetTotalXP()
{
	return this->TotalXP;
}

int ARedemptionPlayerState::GetXPNeededForLevel()
{
	return this->XPNeededForNextLevel;
}


int ARedemptionPlayerState::GetLevel()
{
	return this->Level;
}


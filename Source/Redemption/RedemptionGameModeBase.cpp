// Fill out your copyright notice in the Description page of Project Settings.


#include "RedemptionGameModeBase.h"

#include "RedemptionGameInstance.h"
#include "RedemptionPlayerController.h"
#include "RedemptionState.h"
#include "Blueprint/UserWidget.h"
#include "RedemptionPlayerState.h"
#include "RedemptionGameState.h"

ARedemptionGameModeBase::ARedemptionGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	this->GameStateClass = ARedemptionState::StaticClass();
	this->PlayerControllerClass = ARedemptionPlayerController::StaticClass();
	this->PlayerStateClass = ARedemptionPlayerState::StaticClass();
	this->GameStateClass = ARedemptionGameState::StaticClass();
}

void ARedemptionGameModeBase::BeginPlay()
{
	this->GameInstance = Cast<URedemptionGameInstance>(this->GetWorld()->GetGameInstance());

	if (this->GameInstance)
	{
		this->GameInstance->StartSession(this);
	}

	Super::BeginPlay();
}

void ARedemptionGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// this will restore memory saves, save the game, and unload it.
	this->GameInstance->EndSession();
}

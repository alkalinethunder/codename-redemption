// Fill out your copyright notice in the Description page of Project Settings.


#include "RedemptionGameModeBase.h"

#include "AssetUtils.h"
#include "Shell.h"
#include "ConsoleWidget.h"
#include "RedemptionGameInstance.h"
#include "RedemptionPlayerController.h"
#include "RedemptionState.h"
#include "DesktopWidget.h"
#include "RedemptionPlayerState.h"
#include "RedemptionGameState.h"
#include "ShellManagementActor.h"
#include "ShellCommandAsset.h"

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

	for (UObject* commandAsset : UAssetUtils::LoadAssetsOfClass(UShellCommandAsset::StaticClass()))
	{
		UShellCommandAsset* asset = Cast<UShellCommandAsset>(commandAsset);
		if (asset)
		{
			this->ShellCommands.Add(asset);
		}
	}
	
	if (this->GameInstance)
	{
		this->GameInstance->StartSession(this);

		this->ShellManager = this->GetWorld()->SpawnActor<AShellManagementActor>();
	}

	Super::BeginPlay();
}

void ARedemptionGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// this will restore memory saves, save the game, and unload it.
	this->ShellManager->Destroy();
	this->ShellManager = nullptr;
	this->GameInstance->EndSession();
}

UShell* ARedemptionGameModeBase::CreateShell(UConsoleWidget* InConsoleWidget)
{
	check(InConsoleWidget);
	check(this->ShellManager);

	return this->ShellManager->CreateShell(InConsoleWidget);
}

UShellCommandAsset* ARedemptionGameModeBase::FindCommand(FString InName)
{
	UShellCommandAsset* result = nullptr;

	for (UShellCommandAsset* command : this->ShellCommands)
	{
		if (command->Name == InName)
		{
			result = command;
			break;
		}
	}
	
	return result;
}

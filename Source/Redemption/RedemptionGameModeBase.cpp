// Fill out your copyright notice in the Description page of Project Settings.


#include "RedemptionGameModeBase.h"

#include "AssetUtils.h"
#include "Shell.h"
#include "ConsoleWidget.h"
#include "RedemptionGameInstance.h"
#include "RedemptionPlayerController.h"
#include "DesktopWidget.h"
#include "RedemptionPlayerState.h"
#include "RedemptionGameState.h"
#include "ShellManagementActor.h"
#include "ShellCommandAsset.h"
#include "GraphicalAppAsset.h"
#include "NetPage.h"

ARedemptionGameModeBase::ARedemptionGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	this->PlayerControllerClass = ARedemptionPlayerController::StaticClass();
	this->PlayerStateClass = ARedemptionPlayerState::StaticClass();
	this->GameStateClass = ARedemptionGameState::StaticClass();
}

void ARedemptionGameModeBase::BeginPlay()
{
	this->GameInstance = Cast<URedemptionGameInstance>(this->GetWorld()->GetGameInstance());

	for (UObject* asset : UAssetUtils::LoadAssetsOfClass(UNetworkAsset::StaticClass()))
	{
		UNetworkAsset* net = Cast<UNetworkAsset>(asset);
		if (net)
		{
			this->NetworkAssets.Add(net);
		}
	}
	
	for (UObject* asset : UAssetUtils::LoadAssetsOfClass(USpecialDeviceAsset::StaticClass()))
	{
		USpecialDeviceAsset* net = Cast<USpecialDeviceAsset>(asset);
		if (net)
		{
			this->SpecialDevices.Add(net);
		}
	}

	
	for (UObject* commandAsset : UAssetUtils::LoadAssetsOfClass(UShellCommandAsset::StaticClass()))
	{
		UShellCommandAsset* asset = Cast<UShellCommandAsset>(commandAsset);
		if (asset)
		{
			this->ShellCommands.Add(asset);
		}
	}

	for (UObject* gappAsset : UAssetUtils::LoadAssetsOfClass(UGraphicalAppAsset::StaticClass()))
	{
		UGraphicalAppAsset* asset = Cast<UGraphicalAppAsset>(gappAsset);
		if (asset)
		{
			this->Apps.Add(asset);
		}
	}
	
	if (this->GameInstance)
	{
		this->GameInstance->StartSession(this);

		this->ShellManager = this->GetWorld()->SpawnActor<AShellManagementActor>();
	}

	for (UObject* asset : UAssetUtils::LoadAssetsOfClass(UNetPage::StaticClass()))
	{
		UNetPage* page = Cast<UNetPage>(asset);
		if (page)
		{
			this->NetPages.Add(page);
		}
	}
	
	Super::BeginPlay();
}

UNetPage* ARedemptionGameModeBase::FindNetPage(FString InHost)
{
	UNetPage* page = nullptr;
	for (UNetPage* test : this->NetPages)
	{
		if (test->HostName == InHost && test->PageWidget)
		{
			page = test;
			break;
		}
	}
	return page;
}


void ARedemptionGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// this will restore memory saves, save the game, and unload it.
	this->ShellManager->Destroy();
	this->ShellManager = nullptr;
	this->GameInstance->EndSession();
}

UShell* ARedemptionGameModeBase::CreateShell(UConsoleWidget* InConsoleWidget, bool InLoginShell)
{
	check(InConsoleWidget);
	check(this->ShellManager);

	return this->ShellManager->CreateShell(InConsoleWidget, InLoginShell);
}

UGraphicalAppAsset* ARedemptionGameModeBase::FindApp(FString InName)
{
	UGraphicalAppAsset* result = nullptr;

	for (UGraphicalAppAsset* app : this->Apps)
	{
		if (app->CommandName == InName)
		{
			result = app;
			break;
		}
	}
	
	return result;
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

TArray<UGraphicalAppAsset*> ARedemptionGameModeBase::GetPrograms()
{
	return this->Apps;
}

TArray<UShellCommandAsset*> ARedemptionGameModeBase::GetCommands()
{
	return this->ShellCommands;
}

TArray<UGraphicalAppAsset*> ARedemptionGameModeBase::GetStartupApps()
{
	TArray<UGraphicalAppAsset*> result;

	for(UGraphicalAppAsset* app : this->Apps)
	{
		if (app->CommandFlags.IsStartup)
		{
			result.Add(app);
		}
	}
	
	return result;
}

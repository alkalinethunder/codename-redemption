// Fill out your copyright notice in the Description page of Project Settings.


#include "RedemptionGameModeBase.h"

#include "AssetUtils.h"
#include "Shell.h"
#include "ConsoleWidget.h"
#include "RedemptionGameInstance.h"
#include "RedemptionPlayerController.h"
#include "DesktopWidget.h"
#include "GameStructUtils.h"
#include "RedemptionPlayerState.h"
#include "RedemptionGameState.h"
#include "ShellManagementActor.h"
#include "ShellCommandAsset.h"
#include "GraphicalAppAsset.h"
#include "NetPage.h"
#include "UserContext.h"

ARedemptionGameModeBase::ARedemptionGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	this->PlayerControllerClass = ARedemptionPlayerController::StaticClass();
	this->PlayerStateClass = ARedemptionPlayerState::StaticClass();
	this->GameStateClass = ARedemptionGameState::StaticClass();
}

void ARedemptionGameModeBase::SpawnSpecialDevices()
{
	for (UNetworkAsset* net : this->NetworkAssets)
	{
		int i = this->GameInstance->GetSaveGame()->FindNetwork(net);
		for (USpecialDeviceAsset* specDev : net->SpecialDevices)
		{
			int devIndex = this->GameInstance->GetSaveGame()->FindDevice(specDev);
			if (devIndex != -1)
			{
				FDevice& devData = this->GameInstance->GetSaveGame()->Devices[devIndex];
				devData.Name = specDev->Name.ToString();
				devData.Hostname = specDev->HostName;
				if (devData.DeviceType != specDev->DeviceType)
				{
					devData.DeviceType = specDev->DeviceType;
					UGameStructUtils::DeleteUnhackedHackables(devData);
				}
				devData.Difficulty = specDev->Difficulty;
				
				FNetwork& netData = this->GameInstance->GetSaveGame()->Networks[i];
				if (!netData.Devices.Contains(devData.Id))
				{
					netData.Devices.Add(devData.Id);
				}
			}
			else
			{
				FDevice dev;
				dev.Id = this->GameInstance->GetSaveGame()->GetNextDeviceId();
				dev.DeviceType = specDev->DeviceType;
				dev.Name = specDev->Name.ToString();
				dev.Hostname = specDev->HostName;
				dev.AssetId = specDev->GetName();
				dev.Difficulty = specDev->Difficulty;
				
				FNetwork& netData = this->GameInstance->GetSaveGame()->Networks[i];
				netData.Devices.Add(dev.Id);
				this->GameInstance->GetSaveGame()->Devices.Add(dev);
			}
		}
	}
}

void ARedemptionGameModeBase::GenerateNetworks()
{
	TArray<UNetworkAsset*> missing;
	for (UNetworkAsset* net : this->NetworkAssets)
	{
		int i = this->GameInstance->GetSaveGame()->FindNetwork(net);
		if (i != -1)
		{
			FNetwork& netRef = this->GameInstance->GetSaveGame()->Networks[i];
			netRef.Name = net->Name.ToString();
			netRef.HostName = net->HostName;
			netRef.Difficulty = net->Difficulty;
		}
		else
		{
			missing.Add(net);
		}
	}

	for (UNetworkAsset* net : missing)
	{
		FNetwork NewNet;
		NewNet.AssetId = net->GetName();
		NewNet.Id = this->GameInstance->GetSaveGame()->GetNextNetworkId();
		NewNet.Name = net->Name.ToString();
		NewNet.HostName = net->HostName;
		NewNet.Difficulty = net->Difficulty;

		this->GameInstance->GetSaveGame()->Networks.Add(NewNet);
	}
}

void ARedemptionGameModeBase::BeginPlay()
{
	this->GameInstance = Cast<URedemptionGameInstance>(this->GetWorld()->GetGameInstance());

	// Load assets.
	UAssetUtils::LoadAssets<UNetworkAsset>(this->NetworkAssets);
	UAssetUtils::LoadAssets<USpecialDeviceAsset>(this->SpecialDevices);	
	UAssetUtils::LoadAssets<UShellCommandAsset>(this->ShellCommands);
	UAssetUtils::LoadAssets<UGraphicalAppAsset>(this->Apps);
	UAssetUtils::LoadAssets<UNetPage>(this->NetPages);
	
	if (this->GameInstance)
	{
		this->GameInstance->StartSession(this);

		this->ShellManager = this->GetWorld()->SpawnActor<AShellManagementActor>();
	}

	this->GenerateNetworks();
	this->SpawnSpecialDevices();
	
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

UShell* ARedemptionGameModeBase::CreateShell(UConsoleWidget* InConsoleWidget, UUserContext* InUserContext, bool InLoginShell)
{
	check(InConsoleWidget);
	check (InUserContext);
	check(this->ShellManager);

	return this->ShellManager->CreateShell(InConsoleWidget, InUserContext, InLoginShell);
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

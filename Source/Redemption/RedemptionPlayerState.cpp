// Fill out your copyright notice in the Description page of Project Settings.


#include "RedemptionPlayerState.h"

#include "AssetUtils.h"
#include "RedemptionGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "RedemptionGameModeBase.h"
#include "RedemptionSaveGame.h"
#include "UpgradeAsset.h"
#include "DesktopWidget.h"
#include "RedemptionGameState.h"

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

void ARedemptionPlayerState::NotifyUpgradeUnlocked()
{
	this->SortUpgrades();
	this->OnUpgradeUnlocked.Broadcast();
}

UDesktopWidget* ARedemptionPlayerState::GetDesktop()
{
	return this->Desktop;
}

TArray<UDesktopEnvironment*> ARedemptionPlayerState::GetDesktopEnvironments()
{
	return this->Desktops;
}

TArray<UUpgradeAsset*> ARedemptionPlayerState::GetAvailableUpgrades()
{
	return this->AvailableUpgrades;
}

TArray<UUpgradeAsset*> ARedemptionPlayerState::GetUnlockedUpgrades()
{
	return this->UnlockedUpgrades;
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

	for (UObject* asset : UAssetUtils::LoadAssetsOfClass(UDesktopEnvironment::StaticClass()))
	{
		UDesktopEnvironment* env = Cast<UDesktopEnvironment>(asset);
		if (env)
		{
			this->Desktops.Add(env);
		}
	}
	
	this->GameState = Cast<ARedemptionGameState>(this->GetWorld()->GetGameState());
	this->GameInstance = Cast<URedemptionGameInstance>(this->GetGameInstance());
	this->GameMode = Cast<ARedemptionGameModeBase>(UGameplayStatics::GetGameMode(this));
	
	this->GameInstance->OnExperienceAdded.AddUniqueDynamic(this, &ARedemptionPlayerState::UpdateSkillState);

	this->GeneratePlayerNetwork();
	
	this->UpdateSkillState();
	this->SortUpgrades();

	this->VirtualFileSystem = NewObject<UVirtualFileSystem>();
	this->VirtualFileSystem->MountRootNode(this->GetSaveGame(), GetPlayerDevice().DiskRoot);

	if (this->GameInstance->GetSaveGame()->PlayerDesktop)
	{
		this->Desktop = CreateWidget<UDesktopWidget, APlayerController>(UGameplayStatics::GetPlayerController(this, 0), this->GameInstance->GetSaveGame()->PlayerDesktop->WidgetClass);
	}
	else
	{
		this->Desktop = CreateWidget<UDesktopWidget, APlayerController>(UGameplayStatics::GetPlayerController(this, 0), this->GameMode->DesktopWidget->WidgetClass);
	}
	this->Desktop->AddToViewport();
}

// Called every frame
void ARedemptionPlayerState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UNetworkNode* ARedemptionPlayerState::GetMyNetwork()
{
	return this->GameState->GetNetworkManager()->GetNetworkNode(this->GetPlayerNetwork().Id);
}

UVirtualFileSystem* ARedemptionPlayerState::GetFileSystem()
{
	return this->VirtualFileSystem;
}

FDevice& ARedemptionPlayerState::GetPlayerDevice()
{
	int index = -1;

	for (int i = 0; i < this->GameInstance->GetSaveGame()->Devices.Num(); i++)
	{
		if (this->GameInstance->GetSaveGame()->Devices[i].DeviceType == EDeviceType::Player)
		{
			index = i;
			break;
		}
	}
	
	check(index > -1);

	return this->GameInstance->GetSaveGame()->Devices[index];
}

FNetwork& ARedemptionPlayerState::GetPlayerNetwork()
{
	int i = -1;
	int devon = this->GetPlayerDevice().Id;
	for (int j = 0; j < this->GameInstance->GetSaveGame()->Networks.Num(); j++)
	{
		if (this->GameInstance->GetSaveGame()->Networks[j].Devices.Contains(devon))
		{
			i = j;
			break;
		}
	}
	check (i != -1);
	return this->GameInstance->GetSaveGame()->Networks[i];
}

void ARedemptionPlayerState::GeneratePlayerNetwork()
{
	bool foundNetwork = false;
	for (FNetwork& net : this->GameInstance->GetSaveGame()->Networks)
	{
		if (this->GameInstance->GetSaveGame()->DeviceTypeExistsInNetwork(net, EDeviceType::Player))
		{
			foundNetwork = true;
			this->GameInstance->GetSaveGame()->PlayernetworkId = net.Id;
			break;
		}
	}

	if (!foundNetwork)
	{
		FDevice device;
		device.Id = this->GameInstance->GetSaveGame()->GetNextDeviceId();
		device.DeviceType = EDeviceType::Player;
		device.Name = "Your Computer";
		device.Hostname = this->GameInstance->GetPlayerName() + "-pc";
		device.LocalIP = "108";
		device.DiskRoot = -1;

		this->GameInstance->GetSaveGame()->Devices.Add(device);
		
		FDevice router;
		router.Id = this->GameInstance->GetSaveGame()->GetNextDeviceId();
		router.DeviceType = EDeviceType::Router;
		router.Name = "Your Router";
		router.LocalIP = "1";
		router.DiskRoot = 0;

		this->GameInstance->GetSaveGame()->Devices.Add(router);
		
		FNetwork newNet;
		newNet.Id = this->GameInstance->GetSaveGame()->GetNextNetworkId();
		newNet.Name = "Your network (" + this->GameInstance->GetPlayerName() + ")";
		newNet.Devices.Add(device.Id);
		newNet.Devices.Add(router.Id);
		newNet.LocalSubnet = "192.168.1";

		this->GameInstance->GetSaveGame()->Networks.Add(newNet);
		this->GameInstance->GetSaveGame()->PlayernetworkId = newNet.Id;
	}
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

void ARedemptionPlayerState::SortUpgrades()
{
	// clear upgrade lists
	this->UnlockedUpgrades.Empty();
	this->AvailableUpgrades.Empty();
	this->UnavailableUpgrades.Empty();
	
	for(UUpgradeAsset* upgrade : this->GameState->GetAllUpgrades())
	{
		if (upgrade->IsUnlocked(this))
		{
			this->UnlockedUpgrades.Add(upgrade);
		}
		else if (upgrade->IsAvailable(this))
		{
			this->AvailableUpgrades.Add(upgrade);
		}
		else
		{
			this->UnavailableUpgrades.Add(upgrade);
		}
	}
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

bool ARedemptionPlayerState::IsUpgradeUnlocked(UUpgradeAsset* Upgrade)
{
	return Upgrade && Upgrade->IsUnlocked(this);
}

bool ARedemptionPlayerState::SetDefaultDesktop(UDesktopEnvironment* InDesktopEnvironment)
{
	if (!InDesktopEnvironment)
		return false;

	if (!InDesktopEnvironment->WidgetClass)
		return false;

	bool result = true;

	for (UUpgradeAsset* upg : InDesktopEnvironment->RequiredUpgrades)
	{
		if (!upg->IsUnlocked(this))
		{
			result = false;
			break;
		}
	}

	if (result)
	{
		this->GameInstance->GetSaveGame()->PlayerDesktop = InDesktopEnvironment;

		APlayerController* owner = this->Desktop->GetOwningPlayer();
		
		this->Desktop->RemoveFromParent();
		this->Desktop = CreateWidget<UDesktopWidget, APlayerController>(owner, InDesktopEnvironment->WidgetClass);
		this->Desktop->AddToViewport();
	}
	
	return result;
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

void ARedemptionPlayerState::ListDesktops()
{
	APlayerController* pc = UGameplayStatics::GetPlayerController(this->GetWorld(), 0);

	for (UDesktopEnvironment* desk : this->Desktops)
	{
		pc->ClientMessage(desk->GetName());
	}
}



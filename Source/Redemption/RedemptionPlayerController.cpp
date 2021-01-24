// Fill out your copyright notice in the Description page of Project Settings.


#include "RedemptionPlayerController.h"
#include "OperatingSystemApp.h"
#include "Blueprint/UserWidget.h"
#include "RedemptionGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "VirtualFileSystem.h"
#include "RedemptionPlayerState.h"
#include "RedemptionGameInstance.h"
#include "RedemptionGameState.h"
#include "GraphicalAppAsset.h"
#include "ShellCommandAsset.h"
#include "DesktopWidget.h"

// Sets default values
ARedemptionPlayerController::ARedemptionPlayerController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARedemptionPlayerController::BeginPlay()
{\
	Super::BeginPlay();
	
	this->GameMode = Cast<ARedemptionGameModeBase>(UGameplayStatics::GetGameMode(this));
	this->GameInstance = Cast<URedemptionGameInstance>(this->GetGameInstance());
	if (this->GameMode)
	{
		this->SetShowMouseCursor(true);
	}
}

// Called every frame
void ARedemptionPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UVirtualFileSystem* ARedemptionPlayerController::GetFileSystem()
{
	ARedemptionPlayerState* state = Cast<ARedemptionPlayerState>(this->PlayerState);

	if (state)
	{
		return state->GetFileSystem();
	}
	else
	{
		return nullptr;
	}
}

TArray<UChatContact*> ARedemptionPlayerController::GetContacts()
{
	TArray<UChatContact*> result;
	
	for (FString name : this->GameInstance->GetSaveGame()->PlayerContacts)
	{
		UChatContact* contact = Cast<ARedemptionGameState>(this->GetWorld()->GetGameState())->GetContactByName(name);
		if (contact)
		{
			result.Add(contact);
		}
	}

	return result;
}

bool ARedemptionPlayerController::LaunchGraphicalProgram(UGraphicalAppAsset* InApp, UOperatingSystemApp*& OutAppWidget)
{
	bool result = true;

	if (InApp && InApp->WidgetClass)
	{
		ARedemptionPlayerState* playerState = Cast<ARedemptionPlayerState>(this->PlayerState);
		if (playerState)
		{
			UDesktopWidget* desktop = playerState->GetDesktop();
			if (desktop)
			{
				if (InApp->RequiredUpgrade && !InApp->RequiredUpgrade->IsUnlocked(playerState))
				{
					result = false;
				}
				else
				{
					if (InApp->CommandFlags.IsSingleInstance && desktop->SwitchToApp(InApp->WidgetClass, OutAppWidget))
					{
						OutAppWidget->AppAsset = InApp;
						result = true;
					}
					else
					{
						return desktop->LaunchApp(InApp, OutAppWidget);
					}
				}
			}
			else
			{
				result = false;
			}
		}
		else
		{
			result = false;
		}
	}
	else
	{
		result = false;
	}
	
	return result;
}

TArray<UShellCommandAsset*> ARedemptionPlayerController::GetAvailableCommands()
{
	TArray<UShellCommandAsset*> result;

	for (UShellCommandAsset* command : this->GameMode->GetCommands())
	{
		if (command->RequiredUpgrade != nullptr)
		{
			ARedemptionPlayerState* playerState = Cast<ARedemptionPlayerState>(this->PlayerState);

			if (!playerState || !command->RequiredUpgrade->IsUnlocked(playerState))
			{
				continue;
			}
		}

		result.Add(command);
	}
	
	return result;
}

TArray<UGraphicalAppAsset*> ARedemptionPlayerController::GetAvailablePrograms()
{
	TArray<UGraphicalAppAsset*> result;

	for (UGraphicalAppAsset* command : this->GameMode->GetPrograms())
	{
		if (command->RequiredUpgrade != nullptr)
		{
			ARedemptionPlayerState* playerState = Cast<ARedemptionPlayerState>(this->PlayerState);

			if (!playerState || !command->RequiredUpgrade->IsUnlocked(playerState))
			{
				continue;
			}
		}

		result.Add(command);
	}
	
	return result;
}

bool ARedemptionPlayerController::TryGetCommandByName(FString InCommandName, UShellCommandAsset*& OutCommand)
{
	UShellCommandAsset* command = this->GameMode->FindCommand(InCommandName);

	if (command)
	{
		if (command->RequiredUpgrade != nullptr)
		{
			ARedemptionPlayerState* playerState = Cast<ARedemptionPlayerState>(this->PlayerState);

			if (!playerState || !command->RequiredUpgrade->IsUnlocked(playerState))
			{
				return false;
			}
		}

		OutCommand = command;
		return true;
	}
	else
	{
		return false;
	}
}

bool ARedemptionPlayerController::TryGetAppByName(FString InCommandName, UGraphicalAppAsset*& OutApp)
{
	UGraphicalAppAsset* app = this->GameMode->FindApp(InCommandName);

	if (app)
	{
		if (app->RequiredUpgrade != nullptr)
		{
			ARedemptionPlayerState* playerState = Cast<ARedemptionPlayerState>(this->PlayerState);

			if (!playerState || !app->RequiredUpgrade->IsUnlocked(playerState))
			{
				return false;
			}
		}

		OutApp = app;
		return true;

	}
	else
	{
		return false;
	}
}

FString ARedemptionPlayerController::GetUserNameOfPlayer()
{
	return this->GameInstance->GetPlayerName();
}


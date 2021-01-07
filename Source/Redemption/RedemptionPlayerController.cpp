// Fill out your copyright notice in the Description page of Project Settings.


#include "RedemptionPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "RedemptionGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "VirtualFileSystem.h"
#include "RedemptionPlayerState.h"

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


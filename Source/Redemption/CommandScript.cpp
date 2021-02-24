// Fill out your copyright notice in the Description page of Project Settings.


#include "CommandScript.h"
#include "ConsoleWidget.h"
#include "PathUtils.h"
#include "RedemptionGameState.h"
#include "RedemptionPlayerController.h"
#include "NetworkNode.h"
#include "NetworkManager.h"
#include "UserContext.h"
#include "RedemptionPlayerState.h"

UWorld* UCommandScript::GetWorld() const
{
	if (this->Console)
	{
		return this->Console->GetWorld();
	}
	else
	{
		return GEngine->GetWorld();
	}
}

UUserContext* UCommandScript::GetUserContext()
{
	return this->UserContext;
}

void UCommandScript::Complete()
{
	if (!this->bCompleted)
	{
		this->bCompleted = true;
		this->Completed.Broadcast();
		this->Console = nullptr;
	}
}

void UCommandScript::NativeRun()
{
	this->Run();

	if (!this->CommandFlags.ManualCompletionTrigger)
	{
		this->Complete();
	}	
}

FString UCommandScript::GetWorkingPath()
{
	return this->WorkingDirectory;
}

UConsoleWidget* UCommandScript::GetConsole()
{
	return this->Console;
}

UVirtualFileSystem* UCommandScript::GetFileSystem()
{
	ARedemptionPlayerController* player = Cast<ARedemptionPlayerController>(this->Console->GetOwningPlayer());

	if (player)
	{
		return player->GetFileSystem();
	}
	else
	{
		return nullptr;
	}
}

FString UCommandScript::GetCommandName()
{
	return this->Name;
}

TArray<FString> UCommandScript::GetArguments()
{
	return this->Arguments;
}

FString UCommandScript::RelativeToAbsolutePath(FString InPath)
{
	return UPathUtils::GetAbsolutePath(this->WorkingDirectory, InPath);
}

UNetworkManager* UCommandScript::GetNetworkManager()
{
	ARedemptionPlayerController* pc = Cast<ARedemptionPlayerController>(this->GetConsole()->GetOwningPlayer());
	ARedemptionGameState* gs = Cast<ARedemptionGameState>(pc->GetWorld()->GetGameState());
	return gs->GetNetworkManager();
}

UNetworkNode* UCommandScript::GetMyNetwork()
{
	ARedemptionPlayerState* ps = this->GetConsole()->GetOwningPlayer()->GetPlayerState<ARedemptionPlayerState>();
	return ps->GetMyNetwork();
}

bool UCommandScript::IsCompleted()
{
	return this->bCompleted;
}

void UCommandScript::Begin(FString InCommandName, TArray<FString> InArgs, FString InWorkingDirectory,
                           UConsoleWidget* InConsole, FCommandFlags InFlags, UUserContext* InUserContext)
{
	this->UserContext = InUserContext;
	this->Console = InConsole;
	this->Arguments = InArgs;
	this->Name = InCommandName;
	this->WorkingDirectory = InWorkingDirectory;
	this->CommandFlags = InFlags;
	
	this->NativeRun();
}

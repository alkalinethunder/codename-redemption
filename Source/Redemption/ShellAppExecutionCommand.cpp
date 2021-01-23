// Fill out your copyright notice in the Description page of Project Settings.


#include "ShellAppExecutionCommand.h"
#include "Blueprint/Userwidget.h"
#include "ConsoleWidget.h"
#include "GraphicalAppAsset.h"
#include "RedemptionPlayerController.h"

void UShellAppExecutionCommand::NativeRun()
{
	UOperatingSystemApp* OSApp = nullptr;
	if (this->PlayerController->LaunchGraphicalProgram(this->AppAsset, OSApp))
	{
		// todo: handle command arguments.
	}
	else
	{
		this->GetConsole()->WriteLine(FText::FromString(this->GetCommandName() + ": command not found"));	
	}

	Super::NativeRun();
}

void UShellAppExecutionCommand::SetApp(UGraphicalAppAsset* InApp, ARedemptionPlayerController* InPlayerController)
{
	check (InApp);
	check (InPlayerController);

	check (!this->AppAsset);
	check (!this->PlayerController);

	this->AppAsset = InApp;
	this->PlayerController = InPlayerController;
}

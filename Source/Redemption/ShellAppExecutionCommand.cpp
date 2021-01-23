// Fill out your copyright notice in the Description page of Project Settings.


#include "ShellAppExecutionCommand.h"

#include "AppWidget.h"
#include "Blueprint/Userwidget.h"
#include "ConsoleWidget.h"
#include "GraphicalAppAsset.h"
#include "OperatingSystemApp.h"
#include "PathUtils.h"
#include "VirtualFileSystem.h"
#include "RedemptionPlayerController.h"

void UShellAppExecutionCommand::NativeRun()
{
	bool fileCheckPassed = true;
	FString validPath;
	FString validFolder;
	FString absPath = UPathUtils::GetAbsolutePath(this->GetWorkingPath(), FString::Join(this->GetArguments(), TEXT(" ")));
	
	if (this->AppAsset->CommandFlags.bExpectsFileArgument)
	{
		switch (this->AppAsset->CommandFlags.ExpectedFileType)
		{
			case EExpectedFileType::Directory:
				if (this->GetFileSystem()->DirectoryExists(absPath))
				{
					validFolder = absPath;
				}
				else
				{
					this->GetConsole()->WriteLine(FText::FromString(this->GetCommandName() + ": " + absPath + ": Directory not found."));
					fileCheckPassed = false;
				}
				break;
			case EExpectedFileType::File:
				if (this->GetFileSystem()->FileExists(absPath))
				{
					validPath = absPath;
				}
				else
				{
					this->GetConsole()->WriteLine(FText::FromString(this->GetCommandName() + ": " + absPath + ": File not found."));
					fileCheckPassed = false;
				}
				break;
			default:
				if (this->GetFileSystem()->FileExists(absPath))
				{
					validPath = absPath;
				}
				else if (this->GetFileSystem()->DirectoryExists(absPath))
				{
					validFolder = absPath;
				}
				else
				{
					this->GetConsole()->WriteLine(FText::FromString(this->GetCommandName() + ": " + absPath + ": File or directory not found."));
					fileCheckPassed = false;
				}
				break;
		}
	}
	else
	{
		if (this->GetFileSystem()->FileExists(absPath))
		{
			validPath = absPath;
		}
		else if (this->GetFileSystem()->DirectoryExists(absPath))
		{
			validFolder = absPath;
		}
		else
		{
			this->GetConsole()->WriteLine(FText::FromString(this->GetCommandName() + ": " + absPath + ": File or directory not found."));
			fileCheckPassed = false;
		}

	}

	if (fileCheckPassed)
	{
		UOperatingSystemApp* OSApp = nullptr;
		if (this->PlayerController->LaunchGraphicalProgram(this->AppAsset, OSApp))
		{
			if (validPath.TrimEnd().Len())
			{
				OSApp->AppWidget->FileOpened(validPath);
			}

			if (validFolder.TrimEnd().Len())
			{
				OSApp->AppWidget->FolderOpened(validFolder);
			}
		}
		else
		{
			this->GetConsole()->WriteLine(FText::FromString(this->GetCommandName() + ": command not found"));	
		}
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

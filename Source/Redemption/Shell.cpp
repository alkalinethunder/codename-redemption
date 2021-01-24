// Fill out your copyright notice in the Description page of Project Settings.


#include "Shell.h"

#include "AssetUtils.h"
#include "ConsoleWidget.h"
#include "PathUtils.h"
#include "ShellAppExecutionCommand.h"
#include "ShellManagementActor.h"
#include "VirtualFileSystem.h"
#include "RedemptionPlayerController.h"
#include "ShellCommandAsset.h"
#include "GraphicalAppAsset.h"
#include "UsefulTip.h"

void UShell::PrepareFileSystem()
{
	UVirtualFileSystem* fs = this->PlayerController->GetFileSystem();

	// create the system config folder if it doesn't exist already, this is where we
	// hold the OS's hostname text
	if (!fs->DirectoryExists("/etc"))
		fs->MakeDirectory("/etc");

	// Try to load the hostname text from /etc/hostname. If it's not found, we'll generate
	// a default /etc/hostname and use that
	if (!fs->GetFileTextIfFileExists("/etc/hostname", this->Hostname))
	{
		this->Hostname = this->PlayerController->GetUserNameOfPlayer() + "-pc";
		fs->TryWritingTextToFile("/etc/hostname", this->Hostname);
	}
	
}

void UShell::PrintUsefulTips()
{
	this->Console->WriteLine(FText::FromString("Useful tips"));
	this->Console->WriteLine(FText::FromString("-----------"));
	this->Console->WriteLine(FText::GetEmpty());
	
	for (UUsefulTip* tip : this->UsefulTips)
	{
		FText tipText = tip->GetTipText(this->PlayerController);
		if (!FText::TrimPrecedingAndTrailing(tipText).IsEmpty())
		{
			this->Console->Write(FText::FromString(" - "));
			this->Console->WriteLine(tipText);
		}
	}
}

void UShell::PrintCommands()
{
	this->Console->WriteLine(FText::FromString("Commands"));
	this->Console->WriteLine(FText::FromString("--------"));
	this->Console->WriteLine(FText::GetEmpty());

	for (UShellCommandAsset* command : this->PlayerController->GetAvailableCommands())
	{
		if (!command->CommandFlags.IsRunnableByPlayer)
			continue;
		
		this->Console->Write(FText::FromString(" - %4"));
		this->Console->Write(FText::FromString(command->Name));
		this->Console->Write(FText::FromString("%1: "));
		this->Console->WriteLine(command->HelpText);
	}
}

void UShell::PrintPrograms()
{
	this->Console->WriteLine(FText::FromString("Programs"));
	this->Console->WriteLine(FText::FromString("--------"));
	this->Console->WriteLine(FText::GetEmpty());

	for (UGraphicalAppAsset* command : this->PlayerController->GetAvailablePrograms())
	{
		if (!command->CommandFlags.IsRunnableByPlayer)
			continue;
		
		this->Console->Write(FText::FromString(" - %4"));
		this->Console->Write(FText::FromString(command->CommandName));
		this->Console->Write(FText::FromString("%1: "));
		this->Console->WriteLine(command->Description);
	}

}

void UShell::Exit()
{
	if (!this->bExited)
	{
		this->bExited = true;
		this->OnExited.Broadcast();
		this->Console->OnTextSubmitted.RemoveDynamic(this, &UShell::HandleConsoleTextSubmitted);
		this->Console = nullptr;
		this->PlayerController = nullptr;
	}
}

void UShell::HandleConsoleTextSubmitted(FString InText)
{
	if (!this->CurrentCommandScript)
	{
		TArray<FString> parts;
		FString parseError;

		if (this->BreakCommandLine(InText, parts, parseError))
		{
			TArray<FString> args;
			FString name = parts[0];

			for (int i = 1; i < parts.Num(); i++)
			{
				args.Add(parts[i]);
			}

			if (!this->ProcessBuiltin(name, args))
			{
				if (this->ProcessExtern(name, args))
				{
					this->CurrentCommandScript->Begin(
							name,
							args,
							this->WorkingDirectory,
							this->Console,
 							this->CurrentCommandFlags
						);
					return;
				}
				else
				{
					this->Console->Write(FText::FromString("sh: "));
					this->Console->Write(FText::FromString(name));
					this->Console->WriteLine(FText::FromString(": Command not found."));
				}
			}

			this->WritePrompt();
		}
		else
		{
			if (parseError.Len() > 0)
			{
				this->Console->Write(FText::FromString("%3"));
				this->Console->Write(FText::FromString(parseError));
				this->Console->WriteLine(FText::FromString("%1"));
			}
			
			this->WritePrompt();
		}
	}
}

void UShell::HandleCompletedScript()
{
	this->CurrentCommandScript = nullptr;
	this->WritePrompt();
}

void UShell::LinkToConsole(AShellManagementActor* Owner, UConsoleWidget* InConsole)
{
	this->ShellManager = Owner;
	this->Console = InConsole;
	this->PlayerController = Cast<ARedemptionPlayerController>(InConsole->GetOwningPlayer());
	
	// Load in the Useful Tips.
	this->UsefulTips.Empty();
	for (UObject* asset : UAssetUtils::LoadAssetsOfClass(UUsefulTip::StaticClass()))
	{
		UUsefulTip* usefulTip = Cast<UUsefulTip>(asset);
		if (usefulTip)
		{
			this->UsefulTips.Add(usefulTip);
		}
	}

	// Prepare the file system.
	this->PrepareFileSystem();
	
	this->Console->OnTextSubmitted.AddUniqueDynamic(this, &UShell::HandleConsoleTextSubmitted);
	this->WritePrompt();
}

void UShell::MakeLoginShell()
{
	this->IsLoginShell = true;
}

void UShell::WritePrompt()
{
	if (!this->bExited)
	{
		this->Console->Write(FText::FromString(this->Hostname));
		this->Console->Write(FText::FromString(":"));
		this->Console->Write(FText::FromString(this->WorkingDirectory));
		this->Console->Write(FText::FromString("$ "));
	}
}

bool UShell::BreakCommandLine(FString InText, TArray<FString>& OutParts, FString& OutError)
{
	bool inQuote = false;
	bool inEscape = false;
	bool wasLastCharAQuote = false;
	FString word;
	const TCHAR QUOTE_CHAR = '"';
	const TCHAR ESC_CHAR = '\\';
	
	FString trimmed = InText.TrimStartAndEnd();

	if (trimmed.Len() > 0)
	{
		for (int i = 0; i <= trimmed.Len(); i++)
		{
			if (i < trimmed.Len())
			{
				TCHAR c = trimmed[i];

				// end escape codes.
				if (inEscape)
				{
					switch (c)
					{
						case 'n':
							word += '\n';
							break;
						case '\r':
							word += '\r';
							break;
						case 't':
							word += '\t';
							break;
						case 'v':
							word += '\v';
							break;
						default:
							word += c;
							break;
					}

					inEscape = false;
					continue;
				}

				if (wasLastCharAQuote && !FChar::IsWhitespace(c))
				{
					OutError = "expected whitespace after double-quote string.";
					return false;
				}
				
				// begin escape codes.
				if (c == ESC_CHAR)
				{
					inEscape = true;
					continue;
				}

				if (inQuote)
				{
					if (c == QUOTE_CHAR)
					{
						inQuote = false;
						wasLastCharAQuote = true;
					}
					else
					{
						word += c;
					}

					continue;
				}

				wasLastCharAQuote = false;

				if (c == QUOTE_CHAR)
				{
					inQuote = true;
					continue;
				}
				
				if (FChar::IsWhitespace(c))
				{
					if (word.Len() > 0)
					{
						OutParts.Add(word);
					}
					
					word = "";
					continue;
				}

				word += c;
			}
			else
			{
				if (inEscape)
				{
					OutError = "unended escape sequence";
					return false;
				}

				if (inQuote)
				{
					OutError = "unterminated string";
					return false;
				}

				if (word.Len() > 0)
				{
					OutParts.Add(word);
				}
			}
		}

		return true;
	}
	else
	{
		return false;
	}
}

bool UShell::ProcessExtern(FString InName, TArray<FString> InArgs)
{
	UShellCommandAsset* asset = nullptr;
	UGraphicalAppAsset* gAsset = nullptr;
	if (this->PlayerController->TryGetCommandByName(InName, asset) && asset->CommandFlags.IsRunnableByPlayer)
	{
		UCommandScript* script = NewObject<UCommandScript>(this, asset->CommandScriptClass);

		this->CurrentCommandScript = script;
		this->CurrentCommandScript->Completed.AddUniqueDynamic(this, &UShell::HandleCompletedScript);
		this->CurrentCommandFlags = asset->CommandFlags;
		
		return true;
	}
	else if (this->PlayerController->TryGetAppByName(InName, gAsset) && gAsset->CommandFlags.IsRunnableByPlayer)
	{
		this->CurrentCommandFlags = gAsset->CommandFlags;
		UShellAppExecutionCommand* script = NewObject<UShellAppExecutionCommand>();
		script->SetApp(gAsset, this->PlayerController);
		this->CurrentCommandScript = script;
		this->CurrentCommandScript->Completed.AddUniqueDynamic(this, &UShell::HandleCompletedScript);
		
		return true;
	}
	else
	{
		return false;		
	}
}

bool UShell::RequestExit()
{
	if (this->bExited)
		return true;
	
	if (this->CurrentCommandScript != nullptr)
		return false;

	if (this->IsLoginShell)
		return false;

	this->Exit();
	return true;
}


bool UShell::ProcessBuiltin(FString InName, TArray<FString> InArgs)
{
	if (InName == "clear")
	{
		this->Console->ClearScreen();
		return true;
	}
	else if (InName == "help")
	{
		// Header
		this->Console->WriteLine(FText::FromString("Shell Help"));
		this->Console->WriteLine(FText::FromString("=========="));
		this->Console->WriteLine(FText::GetEmpty());
		
		// Useful Tips
		this->PrintUsefulTips();
		this->Console->WriteLine(FText::GetEmpty());
		this->Console->WriteLine(FText::FromString("%2Type %4tips%2 to see these tips.%1"));
		this->Console->WriteLine(FText::GetEmpty());
		
		// Commands
		this->PrintCommands();
		this->Console->WriteLine(FText::GetEmpty());
		this->Console->WriteLine(FText::FromString("%2Type %4commands%2 to see these commands.%1"));
		this->Console->WriteLine(FText::GetEmpty());

		// Programs
		this->PrintPrograms();
		this->Console->WriteLine(FText::GetEmpty());
		this->Console->WriteLine(FText::FromString("%2Type %4programs%2 to see these programs.%1"));
		this->Console->WriteLine(FText::GetEmpty());
		
		return true;
	}
	else if (InName == "tips")
	{
		this->PrintUsefulTips();
		return true;
	}
	else if (InName == "commands")
	{
		this->PrintCommands();
		return true;
	}
	else if (InName == "programs")
	{
		this->PrintPrograms();
		return true;
	}
	else if (InName == "exit")
	{
		if (this->IsLoginShell)
		{
			this->Console->WriteLine(FText::FromString("exit: cannot exit login shell"));
		}
		else
		{
			this->Exit();
		}

		return true;
	}
	else if (InName == "cd")
	{
		FString relPath = FString::Join(InArgs, TEXT(" "));
		FString absPath = UPathUtils::GetAbsolutePath(this->WorkingDirectory, relPath);

		if (this->PlayerController->GetFileSystem()->DirectoryExists(absPath))
		{
			this->WorkingDirectory = absPath;
		}
		else
		{
			this->Console->Write(FText::FromString("cd: "));
			this->Console->Write(FText::FromString(absPath));
			this->Console->WriteLine(FText::FromString(": Directory not found."));
		}

		return true;
	}
	
	
	return false;
}


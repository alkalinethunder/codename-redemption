// Fill out your copyright notice in the Description page of Project Settings.


#include "Shell.h"
#include "ConsoleWidget.h"
#include "PathUtils.h"
#include "ShellManagementActor.h"
#include "VirtualFileSystem.h"

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
	
	this->Console->OnTextSubmitted.AddUniqueDynamic(this, &UShell::HandleConsoleTextSubmitted);
	this->WritePrompt();
}

void UShell::WritePrompt()
{
	this->Console->Write(FText::FromString(this->WorkingDirectory));
	this->Console->Write(FText::FromString("$ "));
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
	UShellCommandAsset* asset;
	if (this->PlayerController->TryGetCommandByName(InName, asset))
	{
		UCommandScript* script = NewObject<UCommandScript>(this, asset->CommandScriptClass);

		this->CurrentCommandScript = script;
		this->CurrentCommandScript->Completed.AddUniqueDynamic(this, &UShell::HandleCompletedScript);
		this->CurrentCommandFlags = asset->CommandFlags;
		
		return true;
	}
	else
	{
		return false;
	}
}


bool UShell::ProcessBuiltin(FString InName, TArray<FString> InArgs)
{
	if (InName == "clear")
	{
		this->Console->ClearScreen();
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


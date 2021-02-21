// Fill out your copyright notice in the Description page of Project Settings.


#include "NmapCommand.h"
#include "NetworkManager.h"
#include "ConsoleWidget.h"
#include "GameStructUtils.h"
#include "Hackable.h"

void UNmapCommand::NativeRun()
{
	FString ip = "";
	if (this->GetArguments().Num())
	{
		ip = this->GetArguments()[0];

		TArray<FHackable> hackables;
		if (this->GetNetworkManager()->GetHackables(this->GetMyNetwork(), ip, hackables))
		{
			for (FHackable hackable : hackables)
			{
				this->GetConsole()->Write(FText::AsNumber(hackable.Port));
				this->GetConsole()->Write(FText::FromString("    "));

				if (hackable.bIsHacked)
				{
					this->GetConsole()->Write(FText::FromString("%2HACKED%1"));
				}
				else
				{
					if (hackable.bHasTrace)
					{
						this->GetConsole()->Write(FText::FromString("filtered"));
					}
					else
					{
						this->GetConsole()->Write(FText::FromString("open"));
					}

					this->GetConsole()->Write(FText::FromString("        "));
					if (!hackable.Name.TrimEnd().Len() || hackable.Name == "<unknown>")
					{
						this->GetConsole()->Write(FText::FromString(UGameStructUtils::GetHackableIdentifier(hackable.HackableType)));	
					}
					else
					{
						this->GetConsole()->Write(FText::FromString(hackable.Name));
					}
				}

				this->GetConsole()->WriteLine(FText::GetEmpty());
			}
		}
		else
		{
			this->GetConsole()->WriteLine(FText::FromString(this->GetCommandName() + ": " + ip + ": Host is unreachable."));
		}
	}
	else
	{
		this->GetConsole()->WriteLine(FText::FromString(this->GetCommandName() + ": usage: " + this->GetCommandName() + " <host or IP address>"));
	}

	Super::NativeRun();
}

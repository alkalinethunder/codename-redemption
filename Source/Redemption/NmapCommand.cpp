// Fill out your copyright notice in the Description page of Project Settings.


#include "NmapCommand.h"
#include "NetworkManager.h"
#include "ConsoleWidget.h"
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

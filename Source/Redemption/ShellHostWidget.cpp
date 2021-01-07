// Fill out your copyright notice in the Description page of Project Settings.


#include "ShellHostWidget.h"


#include "RedemptionGameModeBase.h"
#include "RedemptionPlayerController.h"
#include "Shell.h"

bool UShellHostWidget::RequestExit()
{
	return this->Shell->RequestExit();
}

bool UShellHostWidget::InitShell(bool InLoginShell)
{
	ARedemptionGameModeBase* GameMode = Cast<ARedemptionGameModeBase>(this->GetWorld()->GetAuthGameMode());
	
	if (GameMode)
	{
		this->Shell = GameMode->CreateShell(this->Console);
		return true;
	}

	return false;
}

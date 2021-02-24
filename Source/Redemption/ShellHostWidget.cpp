// Fill out your copyright notice in the Description page of Project Settings.


#include "ShellHostWidget.h"


#include "RedemptionGameModeBase.h"
#include "RedemptionPlayerController.h"
#include "Shell.h"
#include "UserContext.h"

void UShellHostWidget::HandleShellExited()
{
	if (!this->bIHaveAlreadyFuckingDoneThis)
	{
		this->bIHaveAlreadyFuckingDoneThis = true;

		this->OnShellExit.Broadcast();
	}
}

bool UShellHostWidget::RequestExit()
{
	return this->Shell->RequestExit();
}

bool UShellHostWidget::InitShell(UUserContext* InUserContext, bool InLoginShell)
{
	check (InUserContext);
	
	ARedemptionGameModeBase* GameMode = Cast<ARedemptionGameModeBase>(this->GetWorld()->GetAuthGameMode());
	
	if (GameMode)
	{
		this->Shell = GameMode->CreateShell(this->Console, InUserContext, InLoginShell);
		this->Shell->OnExited.AddUniqueDynamic(this, &UShellHostWidget::HandleShellExited);
		return true;
	}

	return false;
}

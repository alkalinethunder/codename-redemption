// Fill out your copyright notice in the Description page of Project Settings.


#include "AppWidget.h"
#include "RedemptionPlayerController.h"
#include "VirtualFileSystem.h"
#include "UserContext.h"

UVirtualFileSystem* UAppWidget::GetFileSystem()
{
	ARedemptionPlayerController* pc = Cast<ARedemptionPlayerController>(this->GetOwningPlayer());
	return pc->GetFileSystem();
}

UUserContext* UAppWidget::GetUserContext()
{
	return this->UserContext;
}

void UAppWidget::SetUserContext(UUserContext* InUserContext)
{
	check (InUserContext);
	check (!this->UserContext);
	this->UserContext = InUserContext;
}

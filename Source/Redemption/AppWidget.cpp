// Fill out your copyright notice in the Description page of Project Settings.


#include "AppWidget.h"
#include "RedemptionPlayerController.h"
#include "VirtualFileSystem.h"

UVirtualFileSystem* UAppWidget::GetFileSystem()
{
	ARedemptionPlayerController* pc = Cast<ARedemptionPlayerController>(this->GetOwningPlayer());
	return pc->GetFileSystem();
}

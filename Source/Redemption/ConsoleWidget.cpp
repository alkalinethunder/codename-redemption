// Fill out your copyright notice in the Description page of Project Settings.


#include "ConsoleWidget.h"

void UConsoleWidget::Write(FText InText)
{
	this->OutputBuffer += InText.ToString();
}

void UConsoleWidget::WriteLine(FText InText)
{
	this->Write(InText);
	this->OutputBuffer += "\r\n";
}

void UConsoleWidget::ClearScreen()
{
	this->OutputBuffer = "";
}

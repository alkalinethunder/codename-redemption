﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "ShellManagementActor.h"
#include "ConsoleWidget.h"
#include "Shell.h"
#include "UserContext.h"


// Sets default values
AShellManagementActor::AShellManagementActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AShellManagementActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShellManagementActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UShell* AShellManagementActor::CreateShell(UConsoleWidget* InConsole, UUserContext* InUserContext, bool InLoginShell)
{
	check (InUserContext);
	
	UShell* NewShell = NewObject<UShell>();
	this->Shells.Add(NewShell);
	NewShell->LinkToConsole(this, InConsole, InUserContext);

	if (InLoginShell)
	{
		NewShell->MakeLoginShell();	
	}
	
	return NewShell;
}
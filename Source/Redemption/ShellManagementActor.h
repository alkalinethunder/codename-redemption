// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ConsoleWidget.h"
#include "Shell.h"
#include "ShellManagementActor.generated.h"

class UUserContext;

UCLASS()
class REDEMPTION_API AShellManagementActor : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TArray<UShell*> Shells;
	
public:
	// Sets default values for this actor's properties
	AShellManagementActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
	UShell* CreateShell(UConsoleWidget* InConsole, UUserContext* InUserContext, bool InLoginShell);
};

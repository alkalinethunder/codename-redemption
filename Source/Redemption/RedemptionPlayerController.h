// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "VirtualFileSystem.h"
#include "ShellCommandAsset.h"
#include "GraphicalAppAsset.h"
#include "RedemptionGameModeBase.h"
#include "ChatContact.h"
#include "RedemptionPlayerController.generated.h"

UCLASS()
class REDEMPTION_API ARedemptionPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	UPROPERTY()
	ARedemptionGameModeBase* GameMode;

	UPROPERTY()
	URedemptionGameInstance* GameInstance;
	
public:
	// Sets default values for this actor's properties
	ARedemptionPlayerController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintPure)
	UVirtualFileSystem* GetFileSystem();

	UFUNCTION(BlueprintPure)
	TArray<UChatContact*> GetContacts();

	UFUNCTION(BlueprintCallable)
	bool LaunchGraphicalProgram(UGraphicalAppAsset* InApp, UOperatingSystemApp*& OutAppWidget);

	UFUNCTION()
	TArray<UShellCommandAsset*> GetAvailableCommands();

	UFUNCTION()
	TArray<UGraphicalAppAsset*> GetAvailablePrograms();
	
	UFUNCTION()
	bool TryGetCommandByName(FString InCommandName, UShellCommandAsset*& OutCommand);

	UFUNCTION()
    bool TryGetAppByName(FString InCommandName, UGraphicalAppAsset*& OutApp);

	UFUNCTION(BlueprintPure)
	FString GetUserNameOfPlayer();
};

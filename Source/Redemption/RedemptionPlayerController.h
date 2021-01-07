// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ShellCommandAsset.h"
#include "GameFramework/PlayerController.h"
#include "RedemptionPlayerController.generated.h"

class UUserWidget;
class ARedemptionGameModeBase;
class UVirtualFileSystem;

UCLASS()
class REDEMPTION_API ARedemptionPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	UPROPERTY()
	ARedemptionGameModeBase* GameMode;
	
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

	UFUNCTION()
	bool TryGetCommandByName(FString InCommandName, UShellCommandAsset*& OutCommand);
};

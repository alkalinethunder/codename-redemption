// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "CommandFlags.h"
#include "CommandScript.generated.h"

class UConsoleWidget;
class UVirtualFileSystem;
class UNetworkManager;
class UNetworkNode;
class UUserContext;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCommandCompletedEvent);

/**
 * An object that encapsulates a Shell Command Script.
 */
UCLASS(Blueprintable, BlueprintType, Abstract)
class REDEMPTION_API UCommandScript : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UUserContext* UserContext;
	
	UPROPERTY()
	FCommandFlags CommandFlags;
	
	UPROPERTY()
	bool bCompleted = false;

	UPROPERTY()
	FString Name;
	
	UPROPERTY()
	TArray<FString> Arguments;

	UPROPERTY()
	FString WorkingDirectory;

	UPROPERTY()
	UConsoleWidget* Console;

public:
	UPROPERTY(BlueprintAssignable)
	FCommandCompletedEvent Completed;
	
protected:
	virtual UWorld* GetWorld() const override;

protected:
	UFUNCTION(BlueprintPure)
	UUserContext* GetUserContext();
	
	UFUNCTION(BlueprintCallable)
	void Complete();
	
	UFUNCTION(BlueprintImplementableEvent)
	void Run();

	UFUNCTION()
	virtual void NativeRun();

	UFUNCTION(BlueprintPure)
	FString GetWorkingPath();

	UFUNCTION(BlueprintPure)
	UConsoleWidget* GetConsole();

	UFUNCTION(BlueprintPure)
	UVirtualFileSystem* GetFileSystem();

	UFUNCTION(BlueprintPure)
	FString GetCommandName();

	UFUNCTION(BlueprintPure)
	TArray<FString> GetArguments();

	UFUNCTION(BlueprintPure)
	FString RelativeToAbsolutePath(FString InPath);

	UFUNCTION(BlueprintPure)
	UNetworkManager* GetNetworkManager();

	UFUNCTION(BlueprintPure)
	UNetworkNode* GetMyNetwork();
	
public:
	UFUNCTION()
	bool IsCompleted();
	
	UFUNCTION()
	void Begin(FString InCommandName, TArray<FString> InArgs, FString InWorkingDirectory, UConsoleWidget* InConsole, FCommandFlags InFlags, UUserContext* InUserContext);
};

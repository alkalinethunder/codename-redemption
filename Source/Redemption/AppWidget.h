// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VirtualFileSystem.h"
#include "AppWidget.generated.h"

class UUserContext;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, Abstract)
class REDEMPTION_API UAppWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UUserContext* UserContext;

protected:
	UFUNCTION(BlueprintPure)
	UVirtualFileSystem* GetFileSystem();

public:
	UFUNCTION(BlueprintPure)
	UUserContext* GetUserContext();
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void FileOpened(const FString& InFilePath);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
    void FolderOpened(const FString& InFilePath);

public:
	UFUNCTION()
	void SetUserContext(UUserContext* InUserContext);
};

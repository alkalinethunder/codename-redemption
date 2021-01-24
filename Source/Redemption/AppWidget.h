// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VirtualFileSystem.h"
#include "AppWidget.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, Abstract)
class REDEMPTION_API UAppWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintPure)
	UVirtualFileSystem* GetFileSystem();

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void FileOpened(const FString& InFilePath);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
    void FolderOpened(const FString& InFilePath);
};

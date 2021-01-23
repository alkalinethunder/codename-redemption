// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AppWidget.generated.h"

class UVirtualFileSystem;

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
	UFUNCTION(BlueprintImplementableEvent)
	void FileOpened(const FString& InFilePath);

	UFUNCTION(BlueprintImplementableEvent)
    void FolderOpened(const FString& InFilePath);
};

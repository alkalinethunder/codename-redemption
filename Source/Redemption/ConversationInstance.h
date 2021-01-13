// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ConversationInstance.generated.h"

class AConversationManager;
class UConversationAppWidget;
class UConversation;

/**
 * 
 */
UCLASS()
class REDEMPTION_API UConversationInstance : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UConversation* MyAsset;
	
	UPROPERTY()
	AConversationManager* ConversationManager;

	UPROPERTY()
	UConversationAppWidget* AppWidget;

public:
	UFUNCTION()
	void SwitchUserInterface(UConversationAppWidget* InApp);
	
	UFUNCTION()
	UConversationAppWidget* GetUserInterface();

	UFUNCTION()
	void DoNotDisturbChanged(bool InDoNotDisturb);

	UFUNCTION()
	AConversationManager* GetConversationManager();
	
	UFUNCTION()
	UConversation* GetConversationAsset();
	
	UFUNCTION()
	void LinkToManager(AConversationManager* InManager, UConversationAppWidget* InWidget, UConversation* InAsset);
};

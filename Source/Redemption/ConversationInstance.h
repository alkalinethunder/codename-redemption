// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChatState.h"
#include "UObject/Object.h"
#include "ConvoChoice.h"
#include "BranchStackEntry.h"
#include "ConvoBranch.h"
#include "ConversationInstance.generated.h"

class AConversationManager;
class UConversationAppWidget;
class UConversation;

/**
 * 
 */
UCLASS(BlueprintType)
class REDEMPTION_API UConversationInstance : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY()
	bool bIsCompleted = false;
	
	UPROPERTY()
	FConvoChoice Choice;
	
	UPROPERTY()
	EChatState State = EChatState::Playing;
	
	UPROPERTY()
	bool bActionSwitchedBranchState = false;
	
	UPROPERTY()
	int BranchCounter = 0;

	UPROPERTY()
	FConvoBranch Branch;
	
	UPROPERTY()
	TArray<FBranchStackEntry> BranchStack;
	
	UPROPERTY()
	UConversation* MyAsset;
	
	UPROPERTY()
	AConversationManager* ConversationManager;

	UPROPERTY()
	UConversationAppWidget* AppWidget;

private:
	UFUNCTION()
	void RestoreConversationOrder();

	UFUNCTION()
	void PopBranchInternal();

	UFUNCTION()
	void Complete();
	
public:
	UFUNCTION()
	void Tick(float DeltaTime);
	
public:
	UFUNCTION()
	void SwitchUserInterface(UConversationAppWidget* InApp);

	UFUNCTION(BlueprintCallable)
	void ChooseAction(FConvoChoice InChoice);

	UFUNCTION()
	bool IsCompleted();
	
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
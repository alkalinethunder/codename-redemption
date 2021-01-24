// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "UpgradeAsset.h"
#include "ConversationManager.h"
#include "Conversation.h"
#include "ChatContact.h"
#include "RedemptionGameModeBase.h"
#include "RedemptionGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FContactAddedEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDoNotDisturbChanged, bool, InIsDoNotDisturb);

UCLASS(BlueprintType)
class REDEMPTION_API ARedemptionGameState : public AGameStateBase
{
	GENERATED_BODY()

private:
	UPROPERTY()
	ARedemptionGameModeBase* MyGameMode;
	
	UPROPERTY()
	bool bDoNotDisturb = false;
	
	UPROPERTY()
	TArray<UChatContact*> Contacts;

	UPROPERTY()
	TArray<UConversation*> Conversations;
	
	UPROPERTY()
	AConversationManager* ConversationManager;
	
	UPROPERTY()
	TArray<UUpgradeAsset*> Upgrades;

	UPROPERTY()
	URedemptionGameInstance* MyGameInstance;

public:
	UPROPERTY(BlueprintAssignable)
	FDoNotDisturbChanged DoNotDisturbChanged;
	
	UPROPERTY(BlueprintAssignable)
	FContactAddedEvent OnContactAdded;
	
public:
	// Sets default values for this actor's properties
	ARedemptionGameState();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
	TArray<UUpgradeAsset*> GetAllUpgrades();

	UFUNCTION()
	UChatContact* GetContactByName(FString InName);

public:
	UFUNCTION(BlueprintPure)
	bool IsDoNotDisturbActive();

	UFUNCTION(BlueprintCallable)
	void ToggleDoNotDisturb();
	
	UFUNCTION(BlueprintPure)
	AConversationManager* GetConversationManager();

	UFUNCTION(BlueprintCallable)
	void ActivateConversation(UChatContact* InContact, UConversationAppWidget* InWidget);
	
public:
	UFUNCTION(Exec)
	void AddContact(FString InContactName);
	
	UFUNCTION(Exec)
	void LoadedContacts();
};

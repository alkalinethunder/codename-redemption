// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "UpgradeAsset.h"
#include "ConversationManager.h"
#include "Conversation.h"
#include "ChatContact.h"
#include "RedemptionGameModeBase.h"
#include "GrapevinePost.h"
#include "RedemptionGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FContactAddedEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDoNotDisturbChanged, bool, InIsDoNotDisturb);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNewsFeedUpdatedEvent, FNewsFeedEntry, InNewEntry);

UCLASS(BlueprintType)
class REDEMPTION_API ARedemptionGameState : public AGameStateBase
{
	GENERATED_BODY()

private:
	UPROPERTY()
	FRandomStream Random;
	
	UPROPERTY()
	TArray<UPerson*> People;
	
	UPROPERTY()
	float SecondsPerDay = 1440.f;

	UPROPERTY()
	float WorldClock = 0.f;

	UPROPERTY()
	int CurrentDay = 0;
	
	UPROPERTY()
	int Hour;

	UPROPERTY()
	int Minute;
	
	UPROPERTY()
	TArray<UGrapevinePost*> GrapevinePosts;
	
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

	UPROPERTY(BlueprintAssignable)
	FOnNewsFeedUpdatedEvent NewsFeedUpdated;

public:
	// Sets default values for this actor's properties
	ARedemptionGameState();

private:
	UFUNCTION()
	void MakeISPs();
	
	UFUNCTION()
	void CreateMissingRouters();
	
	UFUNCTION()
	void AssignLocalIPs();
	
	UFUNCTION()
	FString GeneratePublicIP();
	
	UFUNCTION()
	void AssignIPAddresses();
	
	UFUNCTION()
	void PostGrapevineAds();
	
	UFUNCTION()
    void UpdateFriendlyTime();

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

	UFUNCTION()
	void PostThought(UPerson* InPerson, FString InThoughtText);

	UFUNCTION()
    UPerson* FindPersonById(FString InPersonId);

	UFUNCTION()
    TArray<FNewsFeedEntry> GetNewsFeed();

	UFUNCTION(BlueprintPure)
    bool IsCurrentDay(FDayList InDayList);

	UFUNCTION()
	int GetMinute();

	UFUNCTION()
	int GetHour();
	
public:
	UFUNCTION(Exec)
	void ListDevices();
	
	UFUNCTION(Exec)
	void ListNets();
	
	UFUNCTION(Exec)
	void AddContact(FString InContactName);
	
	UFUNCTION(Exec)
	void LoadedContacts();
};

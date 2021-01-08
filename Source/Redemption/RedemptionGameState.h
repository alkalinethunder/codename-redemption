// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "RedemptionGameState.generated.h"

class UUpgradeAsset;
class AConversationManager;
class UConversation;
class UChatContact;
class URedemptionGameInstance;

UCLASS(BlueprintType)
class REDEMPTION_API ARedemptionGameState : public AGameStateBase
{
	GENERATED_BODY()

private:
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

public:
	UFUNCTION(Exec)
	void AddContact(FString InContactName);
	
	UFUNCTION(Exec)
	void LoadedContacts();
};

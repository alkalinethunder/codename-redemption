// Fill out your copyright notice in the Description page of Project Settings.


#include "RedemptionGameState.h"
#include "UpgradeAsset.h"
#include "Math/Axis.h"
#include "AssetUtils.h"
#include "Conversation.h"
#include "ChatContact.h"
#include "ConversationManager.h"

// Sets default values
ARedemptionGameState::ARedemptionGameState()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARedemptionGameState::BeginPlay()
{
	Super::BeginPlay();

	for (UObject* asset : UAssetUtils::LoadAssetsOfClass(UConversation::StaticClass()))
	{
		UConversation* convo = Cast<UConversation>(asset);
		if (convo)
		{
			this->Conversations.Add(convo);
		}
	}

	for (UObject* asset : UAssetUtils::LoadAssetsOfClass(UChatContact::StaticClass()))
	{
		UChatContact* contact = Cast<UChatContact>(asset);
		if (contact)
		{
			this->Contacts.Add(contact);
		}
	}
	
	for (UObject* asset : UAssetUtils::LoadAssetsOfClass(UUpgradeAsset::StaticClass()))
	{
		UUpgradeAsset* upgrade = Cast<UUpgradeAsset>(asset);
		if (upgrade)
		{
			this->Upgrades.Add(upgrade);
		}
	}

	// Spawn in the conversation manager.
	this->ConversationManager = this->GetWorld()->SpawnActor<AConversationManager>();
}

// Called every frame
void ARedemptionGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

TArray<UUpgradeAsset*> ARedemptionGameState::GetAllUpgrades()
{
	return this->Upgrades;
}


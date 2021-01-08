// Fill out your copyright notice in the Description page of Project Settings.


#include "RedemptionGameState.h"
#include "UpgradeAsset.h"
#include "Math/Axis.h"
#include "AssetUtils.h"
#include "Conversation.h"
#include "ChatContact.h"
#include "RedemptionGameInstance.h"
#include "ConversationManager.h"
#include "Kismet/GameplayStatics.h"
#include "RedemptionSaveGame.h"

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

	this->MyGameInstance = Cast<URedemptionGameInstance>(this->GetWorld()->GetGameInstance());
	
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

UChatContact* ARedemptionGameState::GetContactByName(FString InName)
{
	UChatContact* result = nullptr;
	
	for (UChatContact* contact : this->Contacts)
	{
		if (contact->GetName() == InName)
		{
			result = contact;
			break;
		}
	}

	return result;
}

void ARedemptionGameState::AddContact(FString InContactName)
{
	for (UChatContact* contact : this->Contacts)
	{
		if (contact->GetName() == InContactName)
		{
			this->MyGameInstance->GetSaveGame()->PlayerContacts.Add(InContactName);
			this->OnContactAdded.Broadcast();
		}
	}
}

void ARedemptionGameState::LoadedContacts()
{
	for (UChatContact* contact : this->Contacts)
	{
		UGameplayStatics::GetPlayerController(this->GetWorld(), 0)->ClientMessage(contact->GetName());	
	}
}


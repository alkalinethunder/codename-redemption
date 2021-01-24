// Fill out your copyright notice in the Description page of Project Settings.


#include "RedemptionGameState.h"
#include "UpgradeAsset.h"
#include "Math/Axis.h"
#include "AssetUtils.h"
#include "Conversation.h"
#include "ChatContact.h"
#include "ConversationAppWidget.h"
#include "RedemptionGameInstance.h"
#include "ConversationManager.h"
#include "RedemptionGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "RedemptionSaveGame.h"

// Sets default values
ARedemptionGameState::ARedemptionGameState()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ARedemptionGameState::PostGrapevineAds()
{
	for (UGrapevinePost* post : this->GrapevinePosts)
	{
		if (post->PostType == EGrapevinePostType::DailyAd)
		{
			if (this->Hour == post->PostOnHour && this->IsCurrentDay(post->PostOnDays))
			{
				this->PostThought(post->PostAuthor, post->PostText);				
			}
		}
	}
}

void ARedemptionGameState::UpdateFriendlyTime()
{
	int secsAsInt = static_cast<int>(this->WorldClock);
	int hour = secsAsInt / 60;
	int min = secsAsInt % 60;

	if (this->Minute != min)
	{
		this->Minute = min;
	}

	if (this->Hour != hour)
	{
		this->Hour = hour;
		this->PostGrapevineAds();
	}
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

	for (UObject* asset : UAssetUtils::LoadAssetsOfClass(UPerson::StaticClass()))
	{
		UPerson* person = Cast<UPerson>(asset);
		if (person)
		{
			this->People.Add(person);
		}
	}

	for (UObject* asset : UAssetUtils::LoadAssetsOfClass(UGrapevinePost::StaticClass()))
	{
		UGrapevinePost* post = Cast<UGrapevinePost>(asset);
		if (post)
		{
			this->GrapevinePosts.Add(post);
		}
	}
	
	this->MyGameMode = Cast<ARedemptionGameModeBase>(this->GetWorld()->GetAuthGameMode());

	if (this->MyGameMode)
	{
		this->bDoNotDisturb = this->MyGameMode->bDoNotDisturbEnabled;
	}
	
	// Spawn in the conversation manager.
	this->ConversationManager = this->GetWorld()->SpawnActor<AConversationManager>();

	// resume the day/night cycle
	this->CurrentDay = static_cast<int>(this->MyGameInstance->GetSaveGame()->CurrentDayOfWeek);
	this->WorldClock = this->MyGameInstance->GetSaveGame()->CurrentDaySeconds;
}

// Called every frame
void ARedemptionGameState::Tick(float DeltaTime)
{
	this->WorldClock += DeltaTime * this->MyGameMode->TimeScale;
	if (this->WorldClock >= this->SecondsPerDay)
	{
		this->WorldClock = 0.f;
		this->CurrentDay++;
		if (this->CurrentDay == static_cast<int>(EWeekDay::NUM_EWeekDay))
		{
			this->CurrentDay = 0;
		}
		this->MyGameInstance->GetSaveGame()->CurrentDayOfWeek = static_cast<EWeekDay>(this->CurrentDay);
	}
	this->MyGameInstance->GetSaveGame()->CurrentDaySeconds = this->WorldClock;

	this->UpdateFriendlyTime();

	Super::Tick(DeltaTime);
}

void ARedemptionGameState::PostThought(UPerson* InPerson, FString InThoughtText)
{
	check (InPerson);
	
	FString personId = InPerson->GetName();

	FNewsFeedEntry newsFeedEntry;
	newsFeedEntry.Text = InThoughtText;
	newsFeedEntry.Sender = personId;
	newsFeedEntry.PostedOn = FDateTime::UtcNow();

	this->MyGameInstance->GetSaveGame()->NewsFeedEntries.Add(newsFeedEntry);

	this->NewsFeedUpdated.Broadcast(newsFeedEntry);
}

UPerson* ARedemptionGameState::FindPersonById(FString InPersonId)
{
	UPerson* result = nullptr;

	for (UPerson* person : this->People)
	{
		if (person->GetName() == InPersonId)
		{
			result = person;
			break;
		}
	}
	
	return result;
}

TArray<FNewsFeedEntry> ARedemptionGameState::GetNewsFeed()
{
	return this->MyGameInstance->GetSaveGame()->NewsFeedEntries;
}

bool ARedemptionGameState::IsCurrentDay(FDayList InDayList)
{
	EWeekDay day = static_cast<EWeekDay>(this->CurrentDay);

	switch (day)
	{
	case EWeekDay::Sunday:
		return InDayList.Sunday;
	case EWeekDay::Monday:
		return InDayList.Monday;
	case EWeekDay::Tuesday:
		return InDayList.Tuesday;
	case EWeekDay::Wednesday:
		return InDayList.Wednesday;
	case EWeekDay::Thursday:
		return InDayList.Thursday;
	case EWeekDay::Friday:
		return InDayList.Friday;
	case EWeekDay::Saturday:
		return InDayList.Saturday;
	}

	return false;
}

int ARedemptionGameState::GetMinute()
{
	return this->Minute;
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

bool ARedemptionGameState::IsDoNotDisturbActive()
{
	return this->bDoNotDisturb;
}

void ARedemptionGameState::ToggleDoNotDisturb()
{
	this->bDoNotDisturb = !this->bDoNotDisturb;
	this->DoNotDisturbChanged.Broadcast(this->bDoNotDisturb);
}

AConversationManager* ARedemptionGameState::GetConversationManager()
{
	return this->ConversationManager;
}

void ARedemptionGameState::ActivateConversation(UChatContact* InContact, UConversationAppWidget* InWidget)
{
	// assertions
	check (InContact);
	check (InWidget);

	// set do not disturb state as well as contact information at the top.
	InWidget->SetDoNotDisturb(this->bDoNotDisturb);
	InWidget->SetContactInfo(InContact);
	
	this->MyGameInstance->GetSaveGame()->PostChatLogs(InWidget, InContact);
	
	// first let's ge a list of conversations available to the player.
	TArray<UConversation*> available;
	for (UConversation* convo : this->Conversations)
	{
		if (convo->Contact == InContact && convo->IsAvailable(this->MyGameInstance->GetSaveGame()))
		{
			available.Add(convo);
		}
	}

	// next we need to figure out if there's a conversation in this list that's active.
	UConversation* active = this->ConversationManager->FindFirstActiveConversation(available);

	// if we've found one then let's reactivate it.
	if (active)
	{
		this->ConversationManager->StartConversation(active, InWidget);
		return;
	}

	// present choices to the user
	InWidget->PresentConversationChoices(this->ConversationManager, available);
}

int ARedemptionGameState::GetHour()
{
	return this->Hour;
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


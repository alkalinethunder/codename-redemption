#include "RedemptionState.h"


#include "AssetUtils.h"
#include "RedemptionGameModeBase.h"
#include "RedemptionGameInstance.h"

ARedemptionState::ARedemptionState()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ARedemptionState::BeginPlay()
{
	Super::BeginPlay();

	this->GameMode = Cast<ARedemptionGameModeBase>(this->GetWorld()->GetAuthGameMode());
	this->GameInstance = Cast<URedemptionGameInstance>(this->GetGameInstance());

	for (UObject* asset : UAssetUtils::LoadAssetsOfClass(UPerson::StaticClass()))
	{
		UPerson* person = Cast<UPerson>(asset);
		if (person)
		{
			this->People.Add(person);
		}
	}
}

void ARedemptionState::Tick(float DeltaSeconds)
{
	this->WorldClock += DeltaSeconds * this->GameMode->TimeScale;
	if (this->WorldClock >= this->SecondsPerDay)
	{
		this->WorldClock = 0.f;
		this->CurrentDay++;
		if (this->CurrentDay == static_cast<int>(EWeekDay::NUM_EWeekDay))
		{
			this->CurrentDay = 0;
		}
		this->GameInstance->GetSaveGame()->CurrentDayOfWeek = static_cast<EWeekDay>(this->CurrentDay);
	}
	this->GameInstance->GetSaveGame()->CurrentDaySeconds = this->WorldClock;

	Super::Tick(DeltaSeconds);
}

void ARedemptionState::PostThought(UPerson* InPerson, FString InThoughtText)
{
	check (InPerson);
	
	FString personId = InPerson->GetName();

	FNewsFeedEntry newsFeedEntry;
	newsFeedEntry.Text = InThoughtText;
	newsFeedEntry.Sender = personId;
	newsFeedEntry.PostedOn = FDateTime::UtcNow();

	this->GameInstance->GetSaveGame()->NewsFeedEntries.Add(newsFeedEntry);

	this->NewsFeedUpdated.Broadcast(newsFeedEntry);
}

UPerson* ARedemptionState::FindPersonById(FString InPersonId)
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

TArray<FNewsFeedEntry> ARedemptionState::GetNewsFeed()
{
	return this->GameInstance->GetSaveGame()->NewsFeedEntries;
}

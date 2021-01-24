#include "RedemptionState.h"


#include "AssetUtils.h"
#include "RedemptionGameInstance.h"

void ARedemptionState::BeginPlay()
{
	Super::BeginPlay();

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

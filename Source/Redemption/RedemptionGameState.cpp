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
#include "GameStructUtils.h"
#include "RedemptionGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "RedemptionSaveGame.h"

// Sets default values
ARedemptionGameState::ARedemptionGameState()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

UDeviceTypeRules* ARedemptionGameState::GetDeviceRules(EDeviceType DeviceType)
{
	UDeviceTypeRules* rules = this->DefaultDeviceTypeRules;

	for(UDeviceTypeRules* rule : this->DeviceRules)
	{
		if (rule->DeviceType == DeviceType)
		{
			rules = rule;
			break;
		}
	}
	
	return rules;
}

UNetworkTypeRules* ARedemptionGameState::GetNetworkRules(ENetworkType NetworkType)
{
	UNetworkTypeRules* rules = this->DefaultNetworkRules;

	for (UNetworkTypeRules* ruleSet : this->NetworkTypeRules)
	{
		if (ruleSet->NetworkType == NetworkType)
		{
			rules = ruleSet;
			break;
		}
	}
	
	return rules;
}

void ARedemptionGameState::MakeRoutes()
{
	TArray<int> ispIDs;
	TArray<int> nonIspIDs;

	// Get all network IDs.
	for (FNetwork& net : this->MyGameInstance->GetSaveGame()->Networks)
	{
		if (net.NetworkType == ENetworkType::InternetServiceProvider)
		{
			ispIDs.Add(net.Id);
		}
		else
		{
			nonIspIDs.Add(net.Id);
		}
	}

	// Give all client nets an Internet Service Provider.
	for (int net : nonIspIDs)
	{
		if (!this->MyGameInstance->GetSaveGame()->NetworkHasISP(net))
		{
			for (int isp : ispIDs)
			{
				int connCount = this->MyGameInstance->GetSaveGame()->GetConnectionCount(isp);
				if (connCount < 5)
				{
					FNetRoute route;
					route.Start = net;
					route.End = isp;
					this->MyGameInstance->GetSaveGame()->Routes.Add(route);
				}
			}
		}
	}

	// Connect ISPs to each other, completing the Web.
	for (int isp : ispIDs)
	{
		if (!this->MyGameInstance->GetSaveGame()->NetworkHasISP(isp))
		{
			for (int peer : ispIDs)
			{
				if (peer == isp)
					continue;

				int peerCount = this->MyGameInstance->GetSaveGame()->GetPeerCount(peer);
				if (peerCount < 2)
				{
					FNetRoute route;
					route.Start = isp;
					route.End = peer;
					this->MyGameInstance->GetSaveGame()->Routes.Add(route);
				}
			}
		}
	}
}

void ARedemptionGameState::MakeISPs()
{
	// so there are a few rules to be known here.
	//
	// 1. I should not be coding at 3 AM, but I am anyway, so expect stupidity.
	// 2. There NEEDS to be at least one ISP.
	// 3. And there should be one ISP for every 5 non-ISP nets.
	int isps = 0;
	int nonIsps = 0;

	// So let's count everything up.
	for (const FNetwork& net : this->MyGameInstance->GetSaveGame()->Networks)
	{
		if (net.NetworkType == ENetworkType::InternetServiceProvider)
		{
			isps++;
		}
		else
		{
			nonIsps++;
		}
	}

	// Next we need to figure out how many ISPs are missing.
	// This is done by decreasing our non-ISP net count by 5 in a loop
	// until it hits 0, and decreasing our ISP count by 1 each time we do.
	// If, by the end of this, we have a negative amount of ISPs, we need
	// to generate new ISPs until that negative amount becomes a zero.
	//
	// This feels like that shitty accounting course.
	while (nonIsps > 0)
	{
		isps--;
		nonIsps -= 5;
	}

	// And this is where we generate missing ones.
	while (isps < 0)
	{
		FNetwork isp;
		isp.Id = this->MyGameInstance->GetSaveGame()->GetNextNetworkId();
		isp.NetworkType = ENetworkType::InternetServiceProvider;
		isp.Difficulty = static_cast<EDifficulty>(this->Random.RandRange(static_cast<int>(EDifficulty::Easy), static_cast<int>(EDifficulty::Fucked)));

		this->MyGameInstance->GetSaveGame()->Networks.Add(isp);
		
		isps++;
	}	
}

void ARedemptionGameState::CreateMissingRouters()
{
	for (FNetwork& net : this->MyGameInstance->GetSaveGame()->Networks)
	{
		if (!UGameStructUtils::NetworkHasRouter(this->MyGameInstance, net))
		{
			FDevice router;
			router.Id = this->MyGameInstance->GetSaveGame()->GetNextDeviceId();
			router.Difficulty = net.Difficulty;
			router.Hostname = net.HostName;
			router.Name = net.Name + "'s Router";
			router.DeviceType = EDeviceType::Router;

			this->MyGameInstance->GetSaveGame()->Devices.Add(router);
			net.Devices.Add(router.Id);
		}
	}
}

void ARedemptionGameState::AssignLocalIPs()
{
	for (FNetwork& net : this->MyGameInstance->GetSaveGame()->Networks)
	{
		TArray<FString> takenIPs;
		// pass 1: get taken IP addresses.
		for (FDevice& dev : this->MyGameInstance->GetSaveGame()->Devices)
		{
			if (net.Devices.Contains(dev.Id) && dev.LocalIP.TrimEnd().Len())
			{
				takenIPs.Add(dev.LocalIP);
			}
		}

		// pass 2: fuck I hate this, this is O(n^insanity)
		for (FDevice& dev : this->MyGameInstance->GetSaveGame()->Devices)
		{
			if (net.Devices.Contains(dev.Id) && !dev.LocalIP.TrimEnd().Len())
			{
				int i = 0;
				while (takenIPs.Contains(FString::FromInt(i)))
				{
					i++;
				}

				dev.LocalIP = FString::FromInt(i);
				takenIPs.Add(dev.LocalIP);
			}
		}
	}
	
	
}

FString ARedemptionGameState::GeneratePublicIP()
{
	int b1 = this->Random.RandRange(12, 253);
	int b2 = this->Random.RandRange(12, 253);
	int b3 = this->Random.RandRange(12, 253);
	int b4 = this->Random.RandRange(12, 253);
	return FString::FromInt(b1) + "." + FString::FromInt(b2) + "." + FString::FromInt(b3) + "." + FString::FromInt(b4);
}

void ARedemptionGameState::AssignIPAddresses()
{
	TArray<FString> takenIPs;
	for (FNetwork& net : this->MyGameInstance->GetSaveGame()->Networks)
	{
		if (net.IPAddress.TrimEnd().Len())
		{
			takenIPs.Add(net.IPAddress);
		}
		else
		{
			do
			{
				net.IPAddress = this->GeneratePublicIP();
			} while (takenIPs.Contains(net.IPAddress));
			takenIPs.Add(net.IPAddress);
		}

		if (!net.LocalSubnet.TrimEnd().Len())
		{
			if (this->Random.RandRange(0, 6) % 2 == 0)
			{
				net.LocalSubnet = "192.168.0";
			}
			else
			{
				int b2 = this->Random.RandRange(0, 254);
				net.LocalSubnet = "10." + FString::FromInt(b2) + ".0";
			}
		}
	}
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

	this->DefaultDeviceTypeRules = NewObject<UDeviceTypeRules>();
	this->DefaultDeviceTypeRules->Hackables.Add(EHackableType::Ssh);
	
	this->DefaultNetworkRules = NewObject<UNetworkTypeRules>();
	this->DefaultNetworkRules->RequiredDevices.Add(EDeviceType::Workstation);
	this->DefaultNetworkRules->Hackables.Add(EHackableType::Ssh);
	
	this->MyGameInstance = Cast<URedemptionGameInstance>(this->GetWorld()->GetGameInstance());

	for (UObject* asset : UAssetUtils::LoadAssetsOfClass(UPayload::StaticClass()))
	{
		UPayload* payload = Cast<UPayload>(asset);
		if (payload)
		{
			this->Payloads.Add(payload);
		}
	}
	
	for (UObject* asset : UAssetUtils::LoadAssetsOfClass(UDeviceTypeRules::StaticClass()))
	{
		UDeviceTypeRules* rules = Cast<UDeviceTypeRules>(asset);
		if (rules)
		{
			this->DeviceRules.Add(rules);
		}
	}
	
	for(UObject* asset : UAssetUtils::LoadAssetsOfClass(UNetworkTypeRules::StaticClass()))
	{
		UNetworkTypeRules* rules = Cast<UNetworkTypeRules>(asset);
		if (rules)
		{
			this->NetworkTypeRules.Add(rules);
		}
	}
	
	for (UObject* asset : UAssetUtils::LoadAssetsOfClass(UHackableAsset::StaticClass()))
	{
		UHackableAsset* hackable = Cast<UHackableAsset>(asset);
		if (hackable)
		{
			this->Hackables.Add(hackable);
		}
	}
	
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

	this->MakeISPs();
	this->CreateMissingRouters();
	this->MakeRoutes();
	this->AssignIPAddresses();
	this->AssignLocalIPs();

	this->NetworkManager = NewObject<UNetworkManager>();
	this->NetworkManager->Init(this);
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

ARedemptionGameModeBase* ARedemptionGameState::GetGameMode()
{
	return this->MyGameMode;
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

URedemptionGameInstance* ARedemptionGameState::GetGameInstance()
{
	return this->MyGameInstance;
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

void ARedemptionGameState::GenerateNetworkHackables(int NetworkId)
{
	int netIndex = this->GetGameInstance()->GetSaveGame()->MapNetwork(NetworkId);

	if (netIndex > -1)
	{
		this->GetGameInstance()->GetSaveGame()->Networks[netIndex].Hackables.Empty();

		URedemptionSaveGame* save = this->GetGameInstance()->GetSaveGame();

		UNetworkTypeRules* genRules = this->GetNetworkRules(save->Networks[netIndex].NetworkType);

		if (genRules)
		{
			TArray<EDeviceType> requiredDevices = genRules->RequiredDevices;
			TArray<EHackableType> hackables = genRules->Hackables;

			while (requiredDevices.Num())
			{
				EDeviceType type = requiredDevices[0];

				bool result = false;
				for (FDevice& dev : save->Devices)
				{
					if (save->Networks[netIndex].Devices.Contains(dev.Id) && dev.DeviceType == type)
					{
						this->GenerateHackables(save->MapDevice(dev.Id), dev.Difficulty);
						result = true;
						break;
					}
				}

				if (!result)
				{
					FDevice newDevice;
					newDevice.Id = save->GetNextDeviceId();
					newDevice.Difficulty = save->Networks[netIndex].Difficulty;
					newDevice.DeviceType = type;
					newDevice.LocalIP = save->GetAvailableLocalIP(save->Networks[netIndex].Id);
					save->Devices.Add(newDevice);
					save->Networks[netIndex].Devices.Add(newDevice.Id);

					this->GenerateHackables(save->Devices.Num() - 1, newDevice.Difficulty);
				}
				
				requiredDevices.RemoveAt(0);
			}

			if (!save->Networks[netIndex].HackablesGenerated)
			{
				TArray<int> takenHackables;

				for (EHackableType hType : genRules->Hackables)
				{
						for (int devId : save->Networks[netIndex].Devices)
					{
						int dIndex = save->MapDevice(devId);

						for (int h = 0; h < save->Devices[dIndex].Hackables.Num(); h++)
						{
							int hash = (h * devId) + (h % devId);
							if (save->Devices[dIndex].Hackables[h].HackableType == hType)
							{
								if (!takenHackables.Contains(hash))
								{
									FNetworkHackable nHackable;
									nHackable.DeviceId = devId;
									nHackable.HackableId = h;
									save->Networks[netIndex].Hackables.Add(nHackable);
									takenHackables.Add(hash);
									break;
								}
							}
						}
					}
				}
			}
		}
	}
	
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

UNetworkManager* ARedemptionGameState::GetNetworkManager()
{
	return this->NetworkManager;
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

void ARedemptionGameState::GenerateHackables(int DeviceIndex, EDifficulty Difficulty)
{
	FDevice& dev = this->MyGameInstance->GetSaveGame()->Devices[DeviceIndex];

	if (dev.bNeedsHackables)
	{
		UGameStructUtils::DeleteUnhackedHackables(dev);

		EDeviceType devType = dev.DeviceType;

		UDeviceTypeRules* rules = this->GetDeviceRules(devType);

		if (rules)
		{
			for (EHackableType hType : rules->Hackables)
			{
				TArray<UHackableAsset*> available;
				for (UHackableAsset* hackable : this->Hackables)
				{
					if (hackable->Type == hType)
					{
						available.Add(hackable);
					}	
				}

				if (available.Num())
				{
					int r = available.Num() * 10;
					int i = 0;
					while (r > 0)
					{
						if (i + 1 >= available.Num())
						{
							i = 0;
						}
						else
						{
							i++;
						}

						r -= FMath::RandRange(1, 5);
					}

					FHackable h;
					h.Port = UGameStructUtils::DefaultPort(hType);
					h.Difficulty = available[i]->Difficulty;
					h.HackableType = available[i]->Type;
					h.Name = available[i]->Name.ToString();

					dev.Hackables.Add(h);
				}
				else
				{
					FHackable h;
					h.Name = "<unknown>";
					h.Port = UGameStructUtils::DefaultPort(hType);
					h.HackableType = hType;
					h.Difficulty = dev.Difficulty;

					dev.Hackables.Add(h);
				}
			}

			dev.bNeedsHackables = false;
		}
	}
}

void ARedemptionGameState::ListDevices()
{
	for (FDevice& dev : this->MyGameInstance->GetSaveGame()->Devices)
	{
		FString log = FString::FromInt(dev.Id) + " - name: " + dev.Name + ", host: " + dev.Hostname + ", ip: " + dev.LocalIP + ", type: " + FString::FromInt(static_cast<int>(dev.DeviceType));
		UGameplayStatics::GetPlayerController(this->GetWorld(), 0)->ClientMessage(log);
	}
}

void ARedemptionGameState::ListNets()
{
	for (FNetwork& net : this->MyGameInstance->GetSaveGame()->Networks)
	{
		FString log = FString::FromInt(net.Id) + " - name: " + net.Name + ", hacked: " + (net.IsHacked ? "yes" : "no") + ", public IP: " + net.IPAddress + ", hostname: " + net.HostName;
		UGameplayStatics::GetPlayerController(this->GetWorld(), 0)->ClientMessage(log);
	}
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

void ARedemptionGameState::TraceNetRoute(int Start, int Destination)
{
	UNetworkNode* startNode = this->GetNetworkManager()->GetNetworkNode(Start);
	UNetworkNode* destNode = this->GetNetworkManager()->GetNetworkNode(Destination);

	APlayerController* pc = UGameplayStatics::GetPlayerController(this->GetWorld(), 0);
	
	if (!startNode)
	{
		pc->ClientMessage("non-existent starting network ID.");
		return;
	}

	if (!destNode)
	{
		pc->ClientMessage("non-existent destination network ID.");
		return;
	}

	TArray<UNetworkNode*> trace = startNode->TraceRoute(destNode);

	if (trace.Num())
	{
		for (UNetworkNode* node : trace)
		{
			FString log = FString::FromInt(node->GetNetworkId());
			pc->ClientMessage(log);
		}
	}
	else
	{
		pc->ClientMessage("could not trace a path between the two networks, this is a bug.");
	}
}


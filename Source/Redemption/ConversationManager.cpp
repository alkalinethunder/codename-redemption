// Fill out your copyright notice in the Description page of Project Settings.


#include "ConversationManager.h"
#include "Conversation.h"
#include "Person.h"
#include "ChatContact.h"
#include "Logging/TokenizedMessage.h"
#include "RedemptionGameState.h"
#include "ConversationInstance.h"

// Sets default values
AConversationManager::AConversationManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AConversationManager::HandleDoNotDisturb(bool InDoNotDisturb)
{
	for (UConversationInstance* instance : this->Instances)
	{
		instance->DoNotDisturbChanged(InDoNotDisturb);
	}
}

// Called when the game starts or when spawned
void AConversationManager::BeginPlay()
{
	Super::BeginPlay();
	this->MyGameState = Cast<ARedemptionGameState>(this->GetWorld()->GetGameState());
	this->MyGameState->DoNotDisturbChanged.AddUniqueDynamic(this, &AConversationManager::HandleDoNotDisturb);
}

// Called every frame
void AConversationManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (int i = 0; i < this->Instances.Num(); i++)
	{
		UConversationInstance* instance = this->Instances[i];
		instance->Tick(DeltaTime);
		if (instance->IsCompleted())
		{
			this->Instances.RemoveAt(i);
		}
	}
}

void AConversationManager::AssertBranch(FConvoBranch InBranch)
{
	for (FBranchActionInfo info : InBranch.Actions)
	{
		check (info.ActionToPerform);
	}

	for  (FConvoChoice choice : InBranch.Choices)
	{
		check (choice.ActionToPerform);
	}
}

void AConversationManager::AssertConvoData(UConversation* InConvo)
{
	check (InConvo->Contact);

	for (UPerson* person : InConvo->Contact->ConversationMembers)
	{
		check (person);
	}

	this->AssertBranch(InConvo->RootBranch);
	
	for (FConvoBranch branch : InConvo->Branches)
	{
		this->AssertBranch(branch);
	}
}

UConversationInstance* AConversationManager::FindChat(UConversation* InConversation)
{
	UConversationInstance* result = nullptr;

	for (UConversationInstance* instance : this->Instances)
	{
		if (instance->GetConversationAsset() == InConversation)
		{
			result = instance;
			break;
		}
	}
	
	return result;
}

bool AConversationManager::GetDoNotDisturb()
{
	return this->MyGameState->IsDoNotDisturbActive();
}

UConversation* AConversationManager::FindFirstActiveConversation(TArray<UConversation*> InAssets)
{
	UConversation* result = nullptr;

	for (UConversation* asset : InAssets)
	{
		UConversationInstance* instance = this->FindChat(asset);
		if (instance)
		{
			result = asset;
			break;
		}
	}
	
	return result;
}

void AConversationManager::StartConversation(UConversation* InConversation, UConversationAppWidget* InAppWidget)
{
	check(InAppWidget);
	check(InConversation)
	check(!this->CurrentConvo);

	this->AssertConvoData(InConversation);

	// So here's the thing.
	// I'm caffeinated.
	// And I'm not stoned.
	// So let's think this through.
	//
	// Conversations can continue happening even if the player closes the chat UI.
	//
	// If this happens, the chat will be "inactive," in the sense that it will keep
	// ticking but messages won't be added to the UI (other than notifications if
	// Do Not Disturb is disabled).
	//
	// So essentially...
	//
	// We need to check for existing chats that use this conversation asset.
	//
	// And when we find one, we need to check if there is a UI attached to it.
	//
	// If there is, then that's a bug.
	//
	// If there isn't, then we'll attach the given UI to it and reactivate it.
	//
	// If there is no chat with this asset attached to it, THEN we can create a new one.
	//
	// So let's go.

	// Step 1. Find an existing chat.
	UConversationInstance* existingChat = this->FindChat(InConversation);

	// Step 2, check if it actually was found.
	if (existingChat)
	{
		// Step 2.1, check if it has UI.
		if (existingChat->GetUserInterface() && existingChat->GetUserInterface() != InAppWidget)
		{
			// Buggymcbuggerfucker.
			check(false);
		}

		// Switch the UI.
		existingChat->SwitchUserInterface(InAppWidget);
	}
	else
	{
		// Step 3: spawn the new chat instance.
		UConversationInstance* newChat = NewObject<UConversationInstance>();
		newChat->LinkToManager(this, InAppWidget, InConversation);
		this->Instances.Add(newChat);
	}
}


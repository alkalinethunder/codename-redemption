// Fill out your copyright notice in the Description page of Project Settings.


#include "ConversationManager.h"
#include "Conversation.h"
#include "Person.h"
#include "ChatContact.h"
#include "Logging/TokenizedMessage.h"

// Sets default values
AConversationManager::AConversationManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AConversationManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AConversationManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AConversationManager::AssertBranch(FConvoBranch InBranch)
{
	for (FBranchActionInfo info : InBranch.Actions)
	{
		check (info.Person);
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

void AConversationManager::StartConversation(UConversation* InConversation)
{
	check(InConversation)
	check(!this->CurrentConvo);

	this->AssertConvoData(InConversation);
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "ConversationInstance.h"
#include "ConversationManager.h"
#include "ConversationAppWidget.h"
#include "ConvoChoice.h"
#include "ConvoBranch.h"
#include "Conversation.h"
#include "RedemptionGameInstance.h"
#include "RedemptionGameState.h"

void UConversationInstance::LinkToManager(AConversationManager* InManager, UConversationAppWidget* InWidget, UConversation* InAsset)
{
	check(InAsset);
	check(InManager);
	check(InWidget);

	this->MyAsset = InAsset;
	this->ConversationManager = InManager;
	this->AppWidget = InWidget;

	this->AppWidget->SetConversation(this);

	this->RestoreConversationOrder();
}

void UConversationInstance::Tick(float DeltaTime)
{
	if (this->State == EChatState::Playing)
	{
		if (this->Branch.Actions.Num())
		{
			FBranchActionInfo info = this->Branch.Actions[this->BranchCounter];
			info.ActionToPerform->Run(DeltaTime, this);
			if (info.ActionToPerform->IsFinished())
			{
				info.ActionToPerform->ResetState();

				if (!this->bActionSwitchedBranchState)
				{
					this->BranchCounter++;
					if (this->Branch.Actions.Num() >= this->BranchCounter)
					{
						this->State = EChatState::AwaitingChoices;
						this->AppWidget->PresentChoices(this->Branch.Choices);
					}
				}
			}
		}
		else
		{
			this->PopBranchInternal();
		}
	}
	else if (this->State == EChatState::ExecutingChoice)
	{
		this->Choice.ActionToPerform->Run(DeltaTime, this);
		if (this->Choice.ActionToPerform->IsFinished())
		{
			this->Choice.ActionToPerform->ResetState();
			
			if (!this->bActionSwitchedBranchState)
			{
				this->PopBranchInternal();
			}
		}
	}
}

void UConversationInstance::SwitchUserInterface(UConversationAppWidget* InApp)
{
	if (this->AppWidget)
	{
		// TODO: unlink the UI.
		this->AppWidget = nullptr;
	}

	check(InApp);
	
	this->AppWidget = InApp;
	this->AppWidget->SetConversation(this);
}

void UConversationInstance::ChooseAction(FConvoChoice InChoice)
{
	if (this->State == EChatState::AwaitingChoices)
	{
		this->Choice = InChoice;
		this->State = EChatState::ExecutingChoice;
		this->AppWidget->HideChoices();
	}
}

bool UConversationInstance::IsCompleted()
{
	return this->bIsCompleted;
}

UConversationAppWidget* UConversationInstance::GetUserInterface()
{
	return this->AppWidget;
}

void UConversationInstance::DoNotDisturbChanged(bool InDoNotDisturb)
{
	this->AppWidget->SetDoNotDisturb(InDoNotDisturb);
}

AConversationManager* UConversationInstance::GetConversationManager()
{
	return this->ConversationManager;
}

UConversation* UConversationInstance::GetConversationAsset()
{
	return this->MyAsset;
}

void UConversationInstance::RestoreConversationOrder()
{
	this->State = EChatState::Playing;
	this->Branch = this->MyAsset->RootBranch;
	this->BranchCounter = 0;
	this->BranchStack.Empty();
}

void UConversationInstance::PopBranchInternal()
{
	if (this->BranchStack.Num())
	{
		FBranchStackEntry entry = this->BranchStack.Pop();

		if (entry.BranchId == NAME_None)
		{
			this->Branch = this->MyAsset->RootBranch;
		}
		else
		{
			bool found = false;
		
			for (FConvoBranch b : this->MyAsset->Branches)
			{
				if (b.Id == entry.BranchId)
				{
					this->Branch = b;
					found = true;
					break;
				}
			}

			check (found);
		}

		this->BranchCounter = entry.BranchPosition;
	}
	else
	{
		this->Complete();
	}
}

void UConversationInstance::Complete()
{
	URedemptionGameInstance* gInstance = Cast<URedemptionGameInstance>(this->ConversationManager->GetGameInstance());
	gInstance->GetSaveGame()->CompletedChats.AddUnique(this->MyAsset->GetName());
	this->bIsCompleted = true;

	this->AppWidget->UnlinkConversation();

	ARedemptionGameState* gState = Cast<ARedemptionGameState>(this->AppWidget->GetWorld()->GetGameState());

	if (gState)
	{
		gState->ActivateConversation(this->MyAsset->Contact, this->AppWidget);
	}

	this->AppWidget = nullptr;
	this->MyAsset = nullptr;
}

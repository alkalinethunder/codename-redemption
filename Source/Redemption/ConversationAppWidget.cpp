// Fill out your copyright notice in the Description page of Project Settings.


#include "ConversationAppWidget.h"
#include "Person.h"
#include "ConversationInstance.h"
#include "ConversationManager.h"

void UConversationAppWidget::UpdateTypingIndicator()
{
	if (this->Typers.Num())
	{
		if (this->Typers.Num() > 4)
		{
			this->ChatTypingIndicator->SetText(FText::FromString("Several people are typing..."));
		}
		else
		{
			FString typerList;

			int i = 0;			
			for (UPerson* person : this->Typers)
			{
				if (typerList.Len())
				{
					if (i == this->Typers.Num() - 1)
					{
						typerList += " and ";	
					}
					else
					{
						typerList += ", ";
					}
				}

				typerList += person->FullName.ToString();
				i++;
			}

			if (i > 1)
			{
				typerList += " are typing...";
			}
			else
			{
				typerList += " is typing...";
			}

			this->ChatTypingIndicator->SetText(FText::FromString(typerList));
		}

		this->ChatTypingIndicator->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		this->ChatTypingIndicator->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UConversationAppWidget::AddTyper(UPerson* InPerson)
{
	if (!this->Typers.Contains(InPerson))
	{
		this->Typers.Add(InPerson);
		this->UpdateTypingIndicator();
	}
}

void UConversationAppWidget::SetDoNotDisturb(bool InDoNotDisturb)
{
	this->DoNotDisturbBanner->SetVisibility(InDoNotDisturb ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
}

void UConversationAppWidget::SetConversation(UConversationInstance* InConversation)
{
	this->MyConversation = InConversation;

	this->Typers.Empty();

	this->SetDoNotDisturb(this->MyConversation->GetConversationManager()->GetDoNotDisturb());
	this->UpdateTypingIndicator();
}

void UConversationAppWidget::RemoveTyper(UPerson* InPerson)
{
	if (this->Typers.Contains(InPerson))
	{
		this->Typers.Remove(InPerson);
		this->UpdateTypingIndicator();
	}
}

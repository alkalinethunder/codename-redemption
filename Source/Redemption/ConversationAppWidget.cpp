// Fill out your copyright notice in the Description page of Project Settings.


#include "ConversationAppWidget.h"
#include "Person.h"
#include "ConversationInstance.h"
#include "ConversationManager.h"
#include "Components/VerticalBoxSlot.h"

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

void UConversationAppWidget::LockPlayerMessageBox()
{
	this->PlayerMessageEntry->SetText(FText::GetEmpty());
	this->PlayerMessageEntry->SetIsReadOnly(true);
}

void UConversationAppWidget::UnlockPlayerMessageBox()
{
	this->PlayerMessageEntry->SetText(FText::GetEmpty());
	this->PlayerMessageEntry->SetIsReadOnly(false);
}

void UConversationAppWidget::SetPlayerMessageText(const FText& InText)
{
	this->PlayerMessageEntry->SetText(InText);
}

void UConversationAppWidget::HideChoices()
{
	this->ChatChoicesBox->ClearChildren();
	this->ChatChoicesBox->SetVisibility(ESlateVisibility::Collapsed);
	this->ChatScroller->ScrollToEnd();
}

void UConversationAppWidget::PresentChoices(TArray<FConvoChoice> InChoices)
{
	this->ChatChoicesBox->ClearChildren();
	for (FConvoChoice Choice : InChoices)
	{
		UUserWidget* widget = this->CreateChoiceWidget(Choice, this->MyConversation);
		if (widget)
		{
			UVerticalBoxSlot* slot = this->ChatChoicesBox->AddChildToVerticalBox(widget);
			slot->HorizontalAlignment = EHorizontalAlignment::HAlign_Right;
		}
	}

	this->ChatChoicesBox->SetVisibility(ESlateVisibility::Visible);
	this->ChatScroller->ScrollToEnd();
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

	this->HideChoices();
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

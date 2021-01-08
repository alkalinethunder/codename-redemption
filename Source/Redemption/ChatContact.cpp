// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatContact.h"

EPersonalPronoun UChatContact::GetPronoun()
{
	if (this->ConversationMembers.Num() != 0)
		return EPersonalPronoun::NonBinary; // they/them
	return this->ConversationMembers[0]->Pronouns;
}

FString UChatContact::GetUsernameText()
{
	if (this->ConversationMembers.Num() == 1)
	{
		return "@" + this->ConversationMembers[0]->Username;
	}
	else if (this->ConversationMembers.Num() > 1)
	{
		return FString::FromInt(this->ConversationMembers.Num() + 1) + " members";
	}
	else
	{
		return "<invalid>";
	}
}

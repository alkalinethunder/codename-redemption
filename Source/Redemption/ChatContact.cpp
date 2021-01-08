// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatContact.h"

EPersonalPronoun UChatContact::GetPronoun()
{
	if (this->ConversationMembers.Num() != 0)
		return EPersonalPronoun::NonBinary; // they/them
	return this->ConversationMembers[0]->Pronouns;
}

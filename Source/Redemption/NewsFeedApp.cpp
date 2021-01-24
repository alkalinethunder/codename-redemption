// Fill out your copyright notice in the Description page of Project Settings.


#include "NewsFeedApp.h"
#include "RedemptionGameState.h"

void UNewsFeedApp::HandleNewPost(FNewsFeedEntry InNewEntry)
{
	this->PostQueue.Add(InNewEntry);
}

void UNewsFeedApp::NativeConstruct()
{
	this->GameState = Cast<ARedemptionGameState>(this->GetWorld()->GetGameState());
	this->GameState->NewsFeedUpdated.AddUniqueDynamic(this, &UNewsFeedApp::HandleNewPost);
	this->PostQueue = this->GameState->GetNewsFeed();
	Super::NativeConstruct();
}

void UNewsFeedApp::NativeDestruct()
{
	this->GameState->NewsFeedUpdated.RemoveDynamic(this, &UNewsFeedApp::HandleNewPost);
	Super::NativeDestruct();
}

void UNewsFeedApp::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	int i = 0;
	while (i < 10 && this->PostQueue.Num())
	{
		i++;
		FNewsFeedEntry entry = this->PostQueue[0];

		UPerson* person = this->GameState->FindPersonById(entry.Sender);
		this->SpawnNewsFeedPost(person, entry);
		this->PostScroller->ScrollToStart();
		this->PostQueue.RemoveAt(0);
	}
}

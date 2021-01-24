// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Person.h"
#include "NewsFeedEntry.h"
#include "RedemptionState.generated.h"

class URedemptionGameInstance;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNewsFeedUpdatedEvent, FNewsFeedEntry, InNewEntry);

/**
 * 
 */
UCLASS(BlueprintType)
class REDEMPTION_API ARedemptionState : public AGameStateBase
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TArray<UPerson*> People;
	
	UPROPERTY()
	URedemptionGameInstance* GameInstance;

public:
	UPROPERTY(BlueprintAssignable)
	FOnNewsFeedUpdatedEvent NewsFeedUpdated;
	
public:
	virtual void BeginPlay() override;
	
public:
	UFUNCTION()
	void PostThought(UPerson* InPerson, FString InThoughtText);

	UFUNCTION()
	UPerson* FindPersonById(FString InPersonId);

	UFUNCTION()
	TArray<FNewsFeedEntry> GetNewsFeed();
};

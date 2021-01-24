// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "GrapevinePostType.h"
#include "Person.h"
#include "Engine/DataAsset.h"
#include "DayLIst.h"
#include "GrapevinePost.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class REDEMPTION_API UGrapevinePost : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Grapevine Post")
	UPerson* PostAuthor = nullptr;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Grapevine Post")
	FString PostText;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Post Type")
	EGrapevinePostType PostType;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Advertisement Post", meta=(EditCondition="PostType == EGrapevinePostType::DailyAd"))
	int PostOnHour = 0;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Advertisement Post", meta=(EditCondition="PostType == EGrapevinePostType::DailyAd"))
	FDayList PostOnDays;
};

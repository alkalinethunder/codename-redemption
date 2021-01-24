// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DayList.generated.h"

USTRUCT(BlueprintType)
struct REDEMPTION_API FDayList
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool Sunday = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool Monday = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool Tuesday = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool Wednesday = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool Thursday = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool Friday = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool Saturday = true;

};

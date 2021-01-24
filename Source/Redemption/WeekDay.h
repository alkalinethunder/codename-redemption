// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeekDay.generated.h"

UENUM(BlueprintType)
enum class EWeekDay : uint8
{
	Sunday,
	Monday,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
	Saturday,
	// totally not a james dupuis trick here
	NUM_EWeekDay
};

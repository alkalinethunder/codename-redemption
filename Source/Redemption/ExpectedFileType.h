// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ExpectedFileType.generated.h"

UENUM(BlueprintType)
enum class EExpectedFileType : uint8
{
	Any,
	File,
	Directory
};

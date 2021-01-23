// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FileType.generated.h"

UENUM(BlueprintType)
enum class EFileType : uint8
{
	UserData,
	GuiApp,
	ShellProgram,
	Upgrade,
	Contact
};

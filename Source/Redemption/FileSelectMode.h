#pragma once

#include "CoreMinimal.h"
#include "FileSelectMode.generated.h"

UENUM(BlueprintType)
enum class EFileSelectMode : uint8
{
	Open,
	Save,
	OpenFolder,
	CreateFolder
};
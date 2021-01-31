#pragma once

#include "CoreMinimal.h"
#include "HackableType.generated.h"

UENUM(BlueprintType)
enum class EHackableType : uint8
{
	Ftp,
	Ssh,
	Http,
	Https,
	Sql,
	Cast,
	RemoteDesktop,
	Chat,
	Voip
};
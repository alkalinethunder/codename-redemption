// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommandScript.h"
#include "NmapCommand.generated.h"

UCLASS(BlueprintType)
class REDEMPTION_API UNmapCommand : public UCommandScript
{
	GENERATED_BODY()

protected:
	virtual void NativeRun() override;
};

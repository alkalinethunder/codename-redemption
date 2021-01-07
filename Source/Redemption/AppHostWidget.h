// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AppHostWidget.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, Abstract)
class REDEMPTION_API UAppHostWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UNamedSlot* ContentSlot;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AppWidget.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Components/ScrollBox.h"


#include "NetBrowserApp.generated.h"

UCLASS(BlueprintType, Blueprintable, Abstract)
class REDEMPTION_API UNetBrowserApp : public UAppWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UEditableText* AddressBar;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UButton* GoButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UButton* BackButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UButton* ForwardButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UScrollBox* WebContent;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChatLOg.generated.h"

class UChatContact;
class UPerson;

/**
 * 
 */
USTRUCT(BlueprintType)
struct FChatLog
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FString Sender;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FText MessageText;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FDateTime UtcSent;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FString Contact;
};

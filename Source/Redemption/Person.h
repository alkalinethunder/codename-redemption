// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PersonalPronoun.h"
#include "Person.generated.h"

/**
 * Represents a single person/character within the game.
 */
UCLASS(Blueprintable, BlueprintType)
class REDEMPTION_API UPerson : public UDataAsset
{
	GENERATED_BODY()

public:
	/**
	 * The @username of the person, used on their Social Profile.
	 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Metadata")
	FString Username;

	/**
	 * The person's full name, used in all areas of the game.
	 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Metadata")
	FText FullName;

	/**
	 * Profile picture used in conversations and social posts.
	 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Metadata")
	UTexture2D* ProfilePicture;
	
	/**
	 * Determines the person's preferred pronouns.
	 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Metadata")
	EPersonalPronoun Pronouns;
};

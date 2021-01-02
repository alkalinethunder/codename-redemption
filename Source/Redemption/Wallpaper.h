// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture2D.h"
#include "Engine/DataAsset.h"
#include "Wallpaper.generated.h"

UCLASS(Blueprintable, BlueprintType)
class REDEMPTION_API UWallpaper : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Metadata")
    FText Name;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Metadata")
    FText Description;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Metadata")
    FText Author;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Wallpaper")
    UTexture2D* LightVariant;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Wallpaper")
    UTexture2D* DarkVariant;
};

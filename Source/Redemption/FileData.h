// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FileType.h"
#include "FileData.generated.h"


USTRUCT(BlueprintType)
struct REDEMPTION_API FFileData
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int Id;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FString FileName;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	EFileType FileType;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FString DataContent;
};

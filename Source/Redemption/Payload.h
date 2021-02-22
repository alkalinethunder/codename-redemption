#pragma once

#include "CoreMinimal.h"

#include "UpgradeAsset.h"
#include "Engine/DataAsset.h"
#include "Payload.generated.h"

UCLASS(BlueprintType)
class REDEMPTION_API UPayload : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Metadata")
	FText Name;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Metadata")
	FText Description;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Metadata")
	FString CommandName;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Progression")
	UUpgradeAsset* RequiredUpgrade;
};
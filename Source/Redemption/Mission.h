#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayAction.h"
#include "Mission.generated.h"

UCLASS(BlueprintType)
class REDEMPTION_API UMission : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Metadata")
	FText Name;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Metadata")
	FText Description;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Requirements")
	TArray<UMission*> Requirements;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Instanced, Category = "Actions")
	UGameplayAction* ActionOnUnlock;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Instanced, Category = "Actions")
	UGameplayAction* ActionOnFinished;
};
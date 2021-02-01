#pragma once

#include "CoreMinimal.h"
#include "DesktopWidget.h"
#include "UpgradeAsset.h"
#include "Engine/DataAsset.h"
#include "DesktopEnvironment.generated.h"

UCLASS(BlueprintType)
class REDEMPTION_API UDesktopEnvironment : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Metadat")
	FText Name;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Metadat")
	FText Description;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Metadat")
	UTexture2D* PreviewImage;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Desktop")
	TSubclassOf<UDesktopWidget> WidgetClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Progression")
	TArray<UUpgradeAsset*> RequiredUpgrades;
};
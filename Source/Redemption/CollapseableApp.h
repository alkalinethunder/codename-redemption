#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AppWidget.h"
#include "GraphicalAppAsset.h"
#include "OperatingSystemApp.h"
#include "Components/Button.h"
#include "Components/ExpandableArea.h"
#include "Components/TextBlock.h"


#include "CollapseableApp.generated.h"

UCLASS(Blueprintable, BlueprintType, Abstract)
class REDEMPTION_API UCollapseableApp : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UOperatingSystemApp* OperatingSystemApp;
	
protected:
	UPROPERTY(BlueprintReadOnly,meta=(BindWidget))
	UExpandableArea* CollapsePanel;

	UPROPERTY(BlueprintReadOnly,meta=(BindWidget))
	UTextBlock* AppTitle;

	UPROPERTY(BlueprintReadOnly,meta=(BindWidget))
	UNamedSlot* AppArea;

	UPROPERTY(BlueprintReadOnly,meta=(BindWidget))
	UButton* CloseButton;

public:
	UFUNCTION()
	void BindApp(UOperatingSystemApp* InApp);
};
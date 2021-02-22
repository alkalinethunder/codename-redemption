#pragma once

#include "CoreMinimal.h"

#include "FileSelectMode.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Components/TextBlock.h"
#include "ValidatorError.h"
#include "FileSelectBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFileSelectCanceled);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFileSelectedEvent, FString, InPath);
DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(FValidatorError, FFileSelectValidator, FString, InPath);

UCLASS(Blueprintable, BlueprintType, Abstract)
class REDEMPTION_API UFileSelectBase : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Meta=(BindWidget))
	UButton* SelectButton;

	UPROPERTY(BlueprintReadOnly, Meta=(BindWidget))
	UButton* BackButton;

	UPROPERTY(BlueprintReadOnly, Meta=(BindWidget))
	UButton* ForwardButton;

	UPROPERTY(BlueprintReadOnly, Meta=(BindWidget))
	UButton* RefreshButton;

	UPROPERTY(BlueprintReadOnly, Meta=(BindWidget))
	UButton* UpButton;

	UPROPERTY(BlueprintReadOnly, Meta=(BindWidget))
	UTextBlock* PathText;

	UPROPERTY(BlueprintReadOnly, Meta=(BindWidget))
	UEditableText* FileNameBox;

public:
	UPROPERTY(BlueprintAssignable)
	FFileSelectedEvent FileSelected;

	UPROPERTY(BlueprintAssignable)
	FFileSelectCanceled FileSelectCanceled;

	UPROPERTY(BlueprintReadWrite)
	FFileSelectValidator Validator;
	
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta=(ExposeOnSpawn))
	EFileSelectMode FileSelectMode;
};
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "ConversationAppWidget.generated.h"

class UPerson;
class UConversationInstance;

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, Abstract)
class REDEMPTION_API UConversationAppWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UConversationInstance* MyConversation;
	
	UPROPERTY()
	TArray<UPerson*> Typers;

private:
	UFUNCTION()
	void UpdateTypingIndicator();
	
protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* ChatTitle;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* ChatMemberCount;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* ChatAvatar;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UVerticalBox* ChatMemberList;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UBorder* DoNotDisturbBanner;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UScrollBox* ChatScroller;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* ChatTypingIndicator;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UVerticalBox* ChatConversationBox;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UVerticalBox* ChatChoicesBox;

public:
	UFUNCTION()
	void AddTyper(UPerson* InPerson);

	UFUNCTION()
	void SetDoNotDisturb(bool InDoNotDisturb);
	
	UFUNCTION()
	void SetConversation(UConversationInstance* InConversation);
	
	UFUNCTION()
    void RemoveTyper(UPerson* InPerson);
};

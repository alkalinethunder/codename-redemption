// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "ChatContact.h"
#include "ConvoChoice.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "Components/Image.h"
#include "Components/MultiLineEditableText.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "ConversationAppWidget.generated.h"

class UPerson;
class UConversationInstance;
class UConversation;
class AConversationManager;

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

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UMultiLineEditableText* PlayerMessageEntry;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UButton* PlayerSend;
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void SendPlayerMessage(const FText& InMessageText, FDateTime InDateTime);

	UFUNCTION(BlueprintImplementableEvent)
	void SendMessage(const FText& InMessageText, FDateTime InDateTime, UPerson* InPerson);

	UFUNCTION(BlueprintImplementableEvent)
	UUserWidget* CreateChoiceWidget(FConvoChoice InChoice, UConversationInstance* InConversationInstance);

	UFUNCTION(BlueprintImplementableEvent)
    UUserWidget* CreateCpnvoStartWidget(UConversation* InConversation, AConversationManager* InActor);
	
public:
	UFUNCTION()
	void UnlinkConversation();
	
	UFUNCTION(BlueprintCallable)
	void StartConversation(AConversationManager* InManager, UConversation* InAsset);
	
	UFUNCTION()
	void LockPlayerMessageBox();

	UFUNCTION()
    void UnlockPlayerMessageBox();

	UFUNCTION()
    void SetPlayerMessageText(const FText& InText);

	UFUNCTION()
	void HideChoices();
	
	UFUNCTION()
	void PresentChoices(TArray<FConvoChoice> InChoices);
	
	UFUNCTION()
	void AddTyper(UPerson* InPerson);

	UFUNCTION()
	void SetDoNotDisturb(bool InDoNotDisturb);
	
	UFUNCTION()
	void SetConversation(UConversationInstance* InConversation);
	
	UFUNCTION()
    void RemoveTyper(UPerson* InPerson);

	UFUNCTION()
	void SetContactInfo(UChatContact* InContact);

	UFUNCTION()
	void PresentConversationChoices(AConversationManager* InConvoManager, TArray<UConversation*> InAssets);
};

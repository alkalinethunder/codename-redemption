// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ChatAction.generated.h"

class UConversationInstance;

/**
 * Base class for all Chat Actions.
 */
UCLASS(Blueprintable, BlueprintType, EditInlineNew)
class REDEMPTION_API UChatAction : public UObject
{
	GENERATED_BODY()

private:	
	UPROPERTY()
	UConversationInstance* Conversation;
	
	UPROPERTY()
	bool bBegun = false;

	UPROPERTY()
	bool bFinished = false;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void Begin();

	UFUNCTION(BlueprintImplementableEvent)
    void Tick(float InDeltaTime);

	UFUNCTION(BlueprintImplementableEvent)
    void End();

	UFUNCTION(BlueprintImplementableEvent)
    void StateReset();
	
	virtual void NativeStateReset();
	virtual void NativeBegin();
	virtual void NativeTick(float DeltaTime);
	virtual void NativeEnd();

	UFUNCTION(BlueprintCallable)
	void Complete();

	UFUNCTION(BlueprintPure)
	UConversationAppWidget* GetChatUserInterface();

	UFUNCTION(BlueprintPure)
	UConversationInstance* GetConversation();
	
public:
	UFUNCTION()
	bool IsFinished();

	UFUNCTION()
	void ResetState();
	
	UFUNCTION()
	void Run(float DeltaTime, UConversationInstance* InConversationInstance);
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChatAction.h"
#include "Person.h"
#include "SendMessage.generated.h"

/**
 * 
 */
UCLASS()
class REDEMPTION_API USendMessage : public UChatAction
{
	GENERATED_BODY()

private:
	UPROPERTY()
	bool bTyping = false;
	
	UPROPERTY()
	float SecondsLeftInTypeDelay = 0;

	UPROPERTY()
	float SecondsLeftInSendDelay = 0;
	
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UPerson* Person = nullptr;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FText MessageText;

protected:
	virtual void NativeTick(float DeltaTime) override;
	virtual void NativeEnd() override;
	virtual void NativeBegin() override;
	virtual void NativeStateReset() override;
};

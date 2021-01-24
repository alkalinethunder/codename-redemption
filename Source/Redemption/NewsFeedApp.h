// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AppWidget.h"
#include "Components/ScrollBox.h"
#include "NewsFeedApp.generated.h"

class ARedemptionState;

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, Abstract)
class REDEMPTION_API UNewsFeedApp : public UAppWidget
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TArray<FNewsFeedEntry> PostQueue;
	
	UPROPERTY()
	ARedemptionState* GameState;
	
protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta=(BindWidget))
	UScrollBox* PostScroller;

private:
	UFUNCTION()
	void HandleNewPost(FNewsFeedEntry InNewEntry);

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void SpawnNewsFeedPost(UPerson* InPerson, FNewsFeedEntry InEntry);
};

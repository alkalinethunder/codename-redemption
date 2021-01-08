// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ConvoBranch.h"
#include "ConversationManager.generated.h"

class UConversation;

UCLASS(BlueprintType)
class REDEMPTION_API AConversationManager : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UConversation* CurrentConvo;
	
public:
	// Sets default values for this actor's properties
	AConversationManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void AssertBranch(FConvoBranch InBranch);
	
	UFUNCTION()
	void AssertConvoData(UConversation* InConvo);
	
public:
	UFUNCTION()
	void StartConversation(UConversation* InConversation);
};

#pragma once

#include "CoreMinimal.h"
#include "GameplayAction.generated.h"

class ARedemptionGameState;

UCLASS(BlueprintType, Blueprintable, Abstract, EditInlineNew)
class REDEMPTION_API UGameplayAction : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY()
	ARedemptionGameState* GameState;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void ActionRun();

protected:
	virtual void NativeActionRun();

protected:
	UFUNCTION(BlueprintPure)
	ARedemptionGameState* GetGameState();
	
public:
	UFUNCTION()
	void Run(ARedemptionGameState* InGameState);
};
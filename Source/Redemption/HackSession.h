#pragma once

#include "CoreMinimal.h"
#include "HackableInfo.h"
#include "EntryPoint.h"
#include "Hackable.h"
#include "Network.h"
#include "Payload.h"
#include "HackSession.generated.h"

class UUserContext;
class UNetworkNode;
class UNetworkManager; // A friend in deed...
class ARedemptionGameState;

UCLASS()
class REDEMPTION_API UHackSession : public UObject
{
	friend UNetworkManager; // Friends to the end.
	
	GENERATED_BODY()

private:
	UPROPERTY()
	bool bAnalyzedHackables = false;
	
	UPROPERTY()
	TArray<UHackableinfo*> Hackables;
	
	UPROPERTY()
	UEntryPoint* EntryPoint = nullptr;

	UPROPERTY()
	UPayload* Payload;
	
	UPROPERTY()
	int HopsCount;
	
	UPROPERTY()
	UNetworkNode* SourceNetwork = nullptr;

	UPROPERTY()
	UNetworkNode* DestinationNetwork=  nullptr;

	UPROPERTY()
	ARedemptionGameState* GameState = nullptr;

	UPROPERTY()
	UUserContext* UserContext;

	UPROPERTY()
	FString DestinationAddress;
	
private:
	UFUNCTION()
	void SetGameState(ARedemptionGameState* InGameState);
	
	UFUNCTION()
	void SetUserContext(UUserContext* InUserContext);

	UFUNCTION()
	void SetHopsCount(int InHopsCount);

	UFUNCTION()
	void SetSourceNetwork(UNetworkNode* InNetwork);

	UFUNCTION()
	void SetDestinationNetwork(UNetworkNode* InNetwork);

	UFUNCTION()
	void SetDestinationAddress(FString InNetworkAddress);

public:
	UFUNCTION()
	FNetwork& GetNetwork();
	
	UFUNCTION()
	TArray<UHackableinfo*> GetHackables();

	UFUNCTION()
	ARedemptionGameState* GetGameState();
};
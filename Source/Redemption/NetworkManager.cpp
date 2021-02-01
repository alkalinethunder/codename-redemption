// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkManager.h"

#include "RedemptionGameInstance.h"
#include "RedemptionGameState.h"

void UNetworkManager::Init(ARedemptionGameState* InGameState)
{
	check (InGameState);
	check (!this->GameState);

	this->GameState = InGameState;

	// let's create all of our nodes.
	for (FNetwork& net : this->GetGameState()->GetGameInstance()->GetSaveGame()->Networks)
	{
		UNetworkNode* node = NewObject<UNetworkNode>();
		node->Init(this, net.Id);
		this->Nodes.Add(node);
	}

	// now the next step is to go through all of the nodes and link them together.
	for (UNetworkNode* node : this->Nodes)
	{
		// get all connected network IDs.
		TArray<int> connections;
		for (FNetRoute& route : this->GetGameState()->GetGameInstance()->GetSaveGame()->Routes)
		{
			if (route.Start == node->GetNetworkId())
			{
				connections.Add(route.End);
			}
			else if(route.End == node->GetNetworkId())
			{
				connections.Add(route.Start);
			}
		}

		// And then link the nodes together.
		for (int connection : connections)
		{
			UNetworkNode* cNode = this->GetNetworkNode(connection);
			if (cNode && cNode != node)
			{
				node->AddConnection(cNode);
			}
		}
	}
}

ARedemptionGameState* UNetworkManager::GetGameState()
{
	return this->GameState;
}

UNetworkNode* UNetworkManager::GetNetworkNode(int InNetworkId)
{
	UNetworkNode* result = nullptr;

	for (UNetworkNode* node : this->Nodes)
	{
		if (node->GetNetworkId() == InNetworkId)
		{
			result = node;
			break;
		}
	}
	
	return result;
}

bool UNetworkManager::ResolveNetworkAddress(FString IPAddress, UNetworkNode*& OutNetwork)
{
	UNetworkNode* result = nullptr;

	for (UNetworkNode* node : this->Nodes)
	{
		if (node->GetHostName() == IPAddress || node->GetIPAddress() == IPAddress)
		{
			result = node;
			break;
		}
	}
	
	OutNetwork = result;
	return result != nullptr;
}

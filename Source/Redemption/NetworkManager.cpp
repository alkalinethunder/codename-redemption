// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkManager.h"

#include "RedemptionGameInstance.h"
#include "RedemptionGameState.h"
#include "UserContext.h"

UNetworkNode* UNetworkManager::MapNetwork(FString InHost)
{
	UNetworkNode* result = nullptr;

	for (UNetworkNode* node : this->Nodes)
	{
		if (node->GetHostName() == InHost || node->GetIPAddress() == InHost)
		{
			result = node;
			break;
		}
	}
	
	return result;
}

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

UHackSession* UNetworkManager::BeginHack(UUserContext* InUserContext, FString InTargetHost)
{
	check (InUserContext);

	UNetworkNode* origin = this->GetNetworkNode(InUserContext->GetNetwork().Id);

	check(origin);

	UNetworkNode* dest = nullptr;
	if(this->ResolveNetworkAddress(InTargetHost, dest))
	{
		TArray<UNetworkNode*> trace = origin->TraceRoute(dest);
		if (trace.Num())
		{
			UHackSession* hack = NewObject<UHackSession>();
			hack->SetGameState(this->GameState);
			hack->SetUserContext(InUserContext);
			hack->SetSourceNetwork(origin);
			hack->SetDestinationNetwork(dest);
			hack->SetDestinationAddress(InTargetHost);
			hack->SetHopsCount(trace.Num());

			return hack;
		}
	}

	return nullptr;
}

bool UNetworkManager::GetHackables(UNetworkNode* InNetwork, FString InHost, TArray<FHackable>& OutHackables)
{
	if (!InNetwork)
		return false;

	int localDevice;
	if (InNetwork->ResolveLocalDevice(InHost, localDevice))
	{
		this->GameState->GenerateHackables(localDevice, InNetwork->GetDifficulty());
		OutHackables = this->GameState->GetGameInstance()->GetSaveGame()->Devices[localDevice].Hackables;
		return true;
	}
	else
	{
		// So here's the thing...
		// We can easily map public IPs like this to their device IDs in the save file.
		// But that's not how this game works.
		// Ya gotta hack the feckin network BEFORE you can hack its devices.
		// So instead I'll just do what that little programmer brain of mine is thinking...
		// And route to the IP's Network.
		UNetworkNode* dest = this->MapNetwork(InHost);
		if (dest)
		{
			dest->GetHackables(OutHackables);
			return true;
		}
	}
	
	return false;
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

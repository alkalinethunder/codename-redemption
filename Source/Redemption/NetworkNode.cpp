// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkNode.h"
#include "NetworkManager.h"
#include "RedemptionGameInstance.h"
#include "RedemptionGameState.h"

FNetwork& UNetworkNode::GetNetwork()
{
	int index = this->NetworkManager->GetGameState()->GetGameInstance()->GetSaveGame()->GetNetworkIndex(this->NetworkId);
	check (index != -1);
	return this->NetworkManager->GetGameState()->GetGameInstance()->GetSaveGame()->Networks[index];
}

void UNetworkNode::Init(UNetworkManager* InNetManager, int InNetId)
{
	check (InNetManager);
	check (!this->NetworkManager);

	this->NetworkManager = InNetManager;
	this->NetworkId = InNetId;
}

void UNetworkNode::AddConnection(UNetworkNode* InNode)
{
	check (InNode);
	check (InNode != this);
	check (!Connections.Contains(InNode));

	this->Connections.Add(InNode);
}

TArray<UNetworkNode*> UNetworkNode::TraceRoute(UNetworkNode* InDestination)
{
	TArray<UNetworkNode*> route;

	route.Add(this);
	
	if (this->Connections.Contains(InDestination))
	{
		route.Add(InDestination);
	}
	else
	{
		for (UNetworkNode* conn : this->Connections)
		{
			TArray<UNetworkNode*> trace = conn->TraceRoute(InDestination);
			if (trace.Contains(InDestination))
			{
				route.Append(trace);
			}
		}
	}
	
	return route;
}

int UNetworkNode::GetNetworkId()
{
	return this->NetworkId;
}

FString UNetworkNode::GetNetworkName()
{
	return this->GetNetwork().Name;
}

FString UNetworkNode::GetHostName()
{
	FNetwork& net = this->GetNetwork();
	if (net.HostName.Len())
		return net.HostName;
	else
		return this->GetIPAddress();
}

FString UNetworkNode::GetIPAddress()
{
	return this->GetNetwork().IPAddress;
}

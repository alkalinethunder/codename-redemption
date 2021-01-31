// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkNode.h"
#include "NetworkManager.h"

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

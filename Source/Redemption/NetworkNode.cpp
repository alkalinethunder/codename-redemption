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

int UNetworkNode::GetNetworkId()
{
	return this->NetworkId;
}

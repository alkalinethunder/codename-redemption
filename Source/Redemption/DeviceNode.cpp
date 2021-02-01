// Fill out your copyright notice in the Description page of Project Settings.


#include "DeviceNode.h"

void UDeviceNode::Init(UNetworkNode* InNetwork, int InDeviceId)
{
	check (InNetwork);
	check (!this->NetworkNode);

	this->NetworkNode = InNetwork;
	this->DeviceId = InDeviceId;
}

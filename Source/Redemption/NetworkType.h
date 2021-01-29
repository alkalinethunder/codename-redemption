#pragma once

#include "CoreMinimal.h"
#include "NetworkType.generated.h"

UENUM(BlueprintType)
enum class ENetworkType : uint8
{
	/**
	 * Basic home network with a single router, basic security,
	 * one or two computers, and a few mobile devices.
	 */
	Household,

	/**
	 * Banks or other financial buildings, contains multiple ATMs.
	 */
	FinancialInstitution,

	/**
	 * Wi-Fi-enabled automotive.
	 */
	Car,

	/**
	 * A phone, tablet, or other mobile device acting as a wireless hotspot.
	 */
	MobileHotspot,

	/**
	 * Commercial building containing POS systems, security, and sometimes an ATM.
	 */
	Store,

	/**
	 * Generic office/corporate network.
	 */
	Office,

	/**
	 * Places where people gather and get drunk, fucked, entertained, and sometimes all three at once.
	 */
	Entertainment,

	/**
	 * Network connecting lots of other networks together.
	 */
	InternetServiceProvider,

	/**
	 * Good old classic James Dupuis Enumeration Situation over here.
	 */
	NUM_ENetworkType UMETA(Hidden),
};
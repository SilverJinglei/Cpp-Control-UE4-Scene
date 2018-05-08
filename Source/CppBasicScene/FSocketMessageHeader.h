#pragma once

#include "CoreMinimal.h"
#include "Networking.h"


DECLARE_STATS_GROUP(TEXT("UnrealCV"), STATGROUP_UnrealCV, STATCAT_Advanced);

DEFINE_LOG_CATEGORY_STATIC(LogUnrealCV, Log, All);

/**
* a simplified version from FNFSMessageHeader of UnrealEngine4, without CRC check
*/
class FSocketMessageHeader
{
	/** Error checking */
	uint32 Magic = 0;

	/** Payload Size */
	uint32 PayloadSize = 0;

	static uint32 DefaultMagic;
public:
	FSocketMessageHeader(const TArray<uint8>& Payload)
	{
		PayloadSize = Payload.Num();  // What if PayloadSize is 0
		Magic = DefaultMagic;
	}

	/** Add header to payload and send it out */
	static bool WrapAndSendPayload(const TArray<uint8>& Payload, FSocket* Socket);
	/** Receive packages and strip header */
	static bool ReceivePayload(FArrayReader& OutPayload, FSocket* Socket, bool* unknown_error);
};
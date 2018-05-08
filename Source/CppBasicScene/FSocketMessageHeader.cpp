#include "FSocketMessageHeader.h"

uint32 FSocketMessageHeader::DefaultMagic = 0x9E2B83C1;

bool FSocketMessageHeader::WrapAndSendPayload(const TArray<uint8>& Payload, FSocket* Socket)
{
	FSocketMessageHeader Header(Payload);

	FBufferArchive Ar;
	Ar << Header.Magic;
	Ar << Header.PayloadSize;
	Ar.Append(Payload);

	int32 TotalAmountSent = 0; // How many bytes have been sent
	int32 AmountToSend = Ar.Num();
	int NumTrial = 100; // Only try a limited amount of times
						// int ChunkSize = 4096;
	while (AmountToSend > 0)
	{
		int AmountSent = 0;
		// GetData returns a uint8 pointer
		Socket->Send(Ar.GetData() + TotalAmountSent, Ar.Num() - TotalAmountSent, AmountSent);
		NumTrial--;

		if (AmountSent == -1)
		{
			continue;
		}

		if (NumTrial < 0)
		{
			UE_LOG(LogUnrealCV, Error, TEXT("Unable to send. Expect to send %d, sent %d"), Ar.Num(), TotalAmountSent);
			return false;
		}

		UE_LOG(LogUnrealCV, Verbose, TEXT("Sending bytes %d/%d, sent %d"), TotalAmountSent, Ar.Num(), AmountSent);
		AmountToSend -= AmountSent;
		TotalAmountSent += AmountSent;
	}
	check(AmountToSend == 0);
	return true;
}

/* Waiting for data, return false only when disconnected */
bool SocketReceiveAll(FSocket* Socket, uint8* Result, int32 ExpectedSize, bool* unknown_error)
{
	int32 Offset = 0;
	while (ExpectedSize > 0)
	{
		// uint32 PendingDataSize;
		// bool Status = Socket->HasPendingData(PendingDataSize);
		// status = PendingDataSize != 0
		int32 NumRead = 0;
		bool RecvStatus = Socket->Recv(Result + Offset, ExpectedSize, NumRead);
		// bool RecvStatus = Socket->Recv(Result + Offset, ExpectedSize, NumRead, ESocketReceiveFlags::WaitAll);
		// WaitAll is not effective for non-blocking socket, see here https://msdn.microsoft.com/en-us/library/windows/desktop/ms740121(v=vs.85).aspx
		// Check pending data first, see https://msdn.microsoft.com/en-us/library/windows/desktop/ms738573(v=vs.85).aspx

		// ESocketConnectionState ConnectionState = Socket->GetConnectionState();
		// check(NumRead <= ExpectedSize);
		// RecvStatus == BytesRead >= 0
		check(NumRead <= ExpectedSize);

		ESocketErrors LastError = ISocketSubsystem::Get()->GetLastErrorCode();
		// Use this check instead of use return status of recv to ensure backward compatibility
		// Because there is a bug with 4.12 FSocketBSD implementation
		// https://www.unrealengine.com/blog/unreal-engine-4-13-released, Search FSocketBSD::Recv
		if (NumRead == 0 && LastError == ESocketErrors::SE_NO_ERROR) // 0 means gracefully closed
		{
			UE_LOG(LogUnrealCV, Log, TEXT("The connection is gracefully closed by the client."));
			return false; // Socket is disconnected. if -1, keep waiting for data
		}

		if (NumRead == 0 && LastError == ESocketErrors::SE_EWOULDBLOCK)
		{
			continue; // No data and keep waiting
		}

		if (LastError == ESocketErrors::SE_NO_ERROR || LastError == ESocketErrors::SE_EWOULDBLOCK)
		{
			// Got some data and in an expected condition
			Offset += NumRead;
			ExpectedSize -= NumRead;
			continue;
		}
		// LastError == ESocketErrors::SE_EWOULDBLOCK means running a non-block socket."));
		if (LastError == ESocketErrors::SE_ECONNABORTED) // SE_ECONNABORTED
		{
			UE_LOG(LogUnrealCV, Error, TEXT("Connection aborted unexpectly."));
			return false;
		}

		const TCHAR* LastErrorMsg = ISocketSubsystem::Get()->GetSocketError(LastError);
		UE_LOG(LogUnrealCV, Error, TEXT("Unexpected error of socket happend, error %s"), LastErrorMsg);
		if (unknown_error != nullptr) {
			*unknown_error = true;
		}
		return false;
	}
	return true;
}


bool FSocketMessageHeader::ReceivePayload(FArrayReader& OutPayload, FSocket* Socket, bool* unknown_error)
{
	TArray<uint8> HeaderBytes;
	int32 Size = sizeof(FSocketMessageHeader);
	HeaderBytes.AddZeroed(Size);

	if (!SocketReceiveAll(Socket, HeaderBytes.GetData(), Size, unknown_error))
	{
		// false here means socket disconnected.
		// UE_LOG(LogUnrealCV, Error, TEXT("Unable to read header, Socket disconnected."));
		UE_LOG(LogUnrealCV, Log, TEXT("Client disconnected."));
		return false;
	}

	FMemoryReader Reader(HeaderBytes);
	uint32 Magic;
	Reader << Magic;

	if (Magic != FSocketMessageHeader::DefaultMagic)
	{
		UE_LOG(LogUnrealCV, Error, TEXT("Bad network header magic"));
		return false;
	}

	uint32 PayloadSize;
	Reader << PayloadSize;
	if (!PayloadSize)
	{
		UE_LOG(LogUnrealCV, Error, TEXT("Empty payload"));
		return false;
	}

	int32 PayloadOffset = OutPayload.AddUninitialized(PayloadSize);
	OutPayload.Seek(PayloadOffset);
	if (!SocketReceiveAll(Socket, OutPayload.GetData() + PayloadOffset, PayloadSize, unknown_error))
	{
		UE_LOG(LogUnrealCV, Error, TEXT("Unable to read full payload, Socket disconnected."));
		return false;
	}

	// Skip CRC checking in FNFSMessageHeader
	return true;
}
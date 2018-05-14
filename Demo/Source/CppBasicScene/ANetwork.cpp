// Fill out your copyright notice in the Description page of Project Settings.

#include "ANetwork.h"

#include "Sockets.h"
#include "SocketSubsystem.h"
#include "IPv4SubnetMask.h"
#include "IPv4Address.h"
#include "SharedPointer.h"
#include "IPAddress.h"
#include "FNetworkRunnable.h"


FSocket* ANetwork::Socket(0);
bool ANetwork::Connected(false);
FInternetAddr* ANetwork::InetAddr(0);


// Sets default values
ANetwork::ANetwork()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

ANetwork::~ANetwork()
{
	//	if(Connected)
	//		Close();
}

// Called when the game starts or when spawned
void ANetwork::BeginPlay()
{
	Super::BeginPlay();

	Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);
	Socket->SetNonBlocking();

	FString address = TEXT("192.168.0.103");
	int32 port = 8888;
	FIPv4Address ip;
	FIPv4Address::Parse(address, ip);

	TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	addr->SetIp(ip.Value);
	addr->SetPort(port);

	InetAddr = &(*addr);

	NetworkRunnable = new FNetworkRunnable(this);

}

void ANetwork::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Close();
}

bool ANetwork::Connect()
{
	if (!Connected)
		Connected = Socket->Connect(*InetAddr);

	return Connected;
}

void ANetwork::EventLoop(void* data)
{
	while (1)
	{
		if (!Socket)
			break;

		if (!Connected)
			Connect();

		if (Connected)
			Recv();

		FPlatformProcess::Sleep(0.03);

	}
}

void ANetwork::Recv()
{
	uint8 Buf[200] = { 0 };
	int32 BufSize(200);
	int32 BytesRead(0);
	uint8* ptr = Buf;

	Socket->Recv(ptr, 2, BytesRead);
	// 	uint16 DataSize(0);
	// 	memcpy(&DataSize,ptr,2);
	// 	ptr += 2;
	// 
	// 	bool success = Socket->Recv(ptr,DataSize,BytesRead,ESocketReceiveFlags::WaitAll);
	// 	if (success)
	// 	{
	// 		ptr += BytesRead;
	// 	}
}

bool ANetwork::Send(int8* data, int16 size, int32& sent)
{
	bool successful(false);
	if (Connected)
	{
		uint8 buf[1024] = { 0 };
		memcpy(buf, &size, sizeof(int16));
		memcpy(&buf[2], data, size);
		successful = Socket->Send(buf, size + 2, sent);
	}

	return successful;
}

void ANetwork::Close()
{
	//
	//Socket->Close();
	ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(Socket);
	Socket = 0;
	Connected = false;
}

// Called every frame
void ANetwork::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Fill out your copyright notice in the Description page of Project Settings.

#include "SocketActor.h"
#include <string>

// Sets default values
ASocketActor::ASocketActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

ASocketActor::~ASocketActor()
{
	CloseSocket();
}

void ASocketActor::CloseSocket()
{
	Print("Close");

	if (ListenerSocket != nullptr)
	{
		ListenerSocket->Close();
		delete ListenerSocket;

		Print("Close");
	}

	if (ConnectionSocket != nullptr)
	{
		ConnectionSocket->Close();
		delete ConnectionSocket;

		Print("Close");
	}
}

// Called when the game starts or when spawned
void ASocketActor::BeginPlay()
{
	Super::BeginPlay();

	//Root = CreateDefaultSubobject<USceneComponent>(TEXT("SocketRoot"));
	//RootComponent = Root;

	//PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	//PickupMesh->AttachToComponent(Root, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	if (!StartTCPReceiver("RamaSocketListener", "127.0.0.1", 30001))
	{
		UE_LOG(LogTemp, Warning, TEXT("Socket Listener Created!"));
		return;
	}
}

void ASocketActor::Destroyed()
{
	CloseSocket();
}

// Called every frame
void ASocketActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ASocketActor::StartTCPReceiver(const FString &yourChosenSocketName, const FString &theIp, const int32 thePort)
{
	ListenerSocket = CreateListenerSocket(yourChosenSocketName, theIp, thePort);

	if (!ListenerSocket)
	{
		ScreenPrint(FString::Printf(TEXT("StartTCPReceiver>>Listen socket could not be created! ~> %s %d"), *theIp, thePort));
		return false;
	}

	Print("Start Listen!");
	
	GetWorldTimerManager().SetTimer(_listenerTimerHandle, this, &ASocketActor::Accept, .01, true);

	return true;
}

FSocket* ASocketActor::CreateListenerSocket(const FString &yourChosenSocketName, const FString &theIP, const int32 thePort, const int32 receiveBufferSize /*= 2 * 1024 * 1024*/)
{
	uint8 ip4Nums[4];

	if (!FormatIP4ToNumber(theIP, ip4Nums))
	{
		Print("Invalid IP!");
		return nullptr;
	}

	// Create Socket
	FIPv4Endpoint Endpoint(FIPv4Address(ip4Nums[0], ip4Nums[1], ip4Nums[2], ip4Nums[3]), thePort);
	FSocket* listenSocket = 
		FTcpSocketBuilder(*yourChosenSocketName)
		.AsReusable()
		.BoundToEndpoint(Endpoint)
		.Listening(8);
	
	listenSocket->SetRecvErr(true);
	// Set Buffer Size
	int32 newSize = 0;
	listenSocket->SetReceiveBufferSize(receiveBufferSize, newSize);

	return listenSocket;
}

void ASocketActor::Accept()
{
	if (!ListenerSocket) return;

	//LogSocket(TEXT("Listening"));

	//Remote address

	auto ss = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
	if(ss->GetLastErrorCode() != SE_NO_ERROR)
		ScreenPrint(ss->GetSocketError(ss->GetLastErrorCode()));

	bool pending;
	
	// handle incoming connection
	if (ListenerSocket->HasPendingConnection(pending) && pending)
	{
		
		TSharedRef<FInternetAddr> remoteAddress = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();

		Print("Connection Coming!");

		// Already have a connection? destroy previous
		if (ConnectionSocket)
		{
			Print("Destroy current socket!");

			ConnectionSocket->Close();
			ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ConnectionSocket);
		}

		// New connection receive~!
		ConnectionSocket = ListenerSocket->Accept(*remoteAddress, TEXT("RamaTCP received socket connection"));

		if (ConnectionSocket != nullptr)
		{
			//Global cache of current remote address
			RemoteAddressForConnection = FIPv4Endpoint(remoteAddress);

			Print("Accepted Connection! WHOOHO!!!");
			
			GetWorldTimerManager().SetTimer(_receivedTimerHandle, this, &ASocketActor::Read, .01, true);
		}
	}

	//ScreenPrint(FString::Printf(TEXT("%d"), pending));
}

void ASocketActor::Read()
{
	if (!ConnectionSocket) return;

	TArray<uint8> receivedData;

	uint32 Size;

	while (ConnectionSocket->HasPendingData(Size))
	{
		receivedData.Init(0, FMath::Min(Size, 65507u));

		int32 read = 0;
		ConnectionSocket->Recv(receivedData.GetData(), receivedData.Num(), read);

		//this->Print(FString::Printf(TEXT("Data Read! %d"), receivedData.Num()));
	}
	
	if (receivedData.Num() <= 0)
		return;

	ScreenPrint(FString::Printf(TEXT("Total Data read! %d"), receivedData.Num()).GetCharArray().GetData());

	const FString receivedUE4String = StringFromBinaryArray(receivedData);
	auto p = TEXT("As String!!! ~>") + receivedUE4String;
	ScreenPrint(p.GetCharArray().GetData());
}

bool ASocketActor::FormatIP4ToNumber(const FString& theIP, uint8(&Out)[4])
{
	// IP Formatting
	theIP.Replace(TEXT(" "), TEXT(""));


	//String Parts
	TArray<FString> Parts;
	theIP.ParseIntoArray(Parts, TEXT("."), true);

	if (Parts.Num() != 4)
		return false;

	//String to Number Parts
	for (int32 i = 0; i < 4; i++)
	{
		Out[i] = FCString::Atoi(*Parts[i]);
	}

	return true;
}

const FString ASocketActor::StringFromBinaryArray(TArray<uint8>& binaryArray)
{
	binaryArray.Add(0); // Add 0 termination, even if string is already 0-terminated,it doesn't change result.

	return FString(ANSI_TO_TCHAR(reinterpret_cast<const char*>(binaryArray.GetData())));
}
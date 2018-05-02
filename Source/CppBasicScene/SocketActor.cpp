// Fill out your copyright notice in the Description page of Project Settings.

#include "SocketActor.h"
#include <string>

// Sets default values
ASocketActor::ASocketActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("SocketRoot"));
	RootComponent = Root;

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	PickupMesh->AttachToComponent(Root, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

}

// Called when the game starts or when spawned
void ASocketActor::BeginPlay()
{
	Super::BeginPlay();

	if (!StartTCPReceiver("RamaSocketListener", "127.0.0.1", 8890))
	{
		UE_LOG(LogTemp, Warning, TEXT("Socket Listener Created!"));
		return;
	}
}

// Called every frame
void ASocketActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ASocketActor::StartTCPReceiver(const FString &yourChosenSocketName, const FString &theIp, const int32 ThePort)
{
	ListenerSocket = CreateTCPConnectionListener(yourChosenSocketName, theIp, ThePort);

	if (!ListenerSocket)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("StartTCPReceiver>>Listen socket could not be created! ~> %s %d"), *theIp, ThePort));
		return false;
	}

	LogSocket("Start Listen!");

	GetWorldTimerManager().SetTimer(_memberTimerHandle, this, &ASocketActor::TCPConnectionListener, .01, true);

	return true;
}

FSocket* ASocketActor::CreateTCPConnectionListener(const FString &YourChosenSocketName, const FString &TheIP, const int32 ThePort, const int32 receiveBufferSize /*= 2 * 1024 * 1024*/)
{
	uint8 ip4Nums[4];

	if (!FormatIP4ToNumber(TheIP, ip4Nums))
	{
		VShow("Invalid IP!");
		return nullptr;
	}

	// Create Socket
	FIPv4Endpoint Endpoint(FIPv4Address(ip4Nums[0], ip4Nums[1], ip4Nums[2], ip4Nums[3]), ThePort);
	FSocket* listenSocket = FTcpSocketBuilder(*YourChosenSocketName).AsReusable().BoundToEndpoint(Endpoint).Listening(8);

	// Set Buffer Size
	int32 newSize = 0;
	listenSocket->SetReceiveBufferSize(receiveBufferSize, newSize);

	return listenSocket;
}

void ASocketActor::TCPConnectionListener()
{
	if (!ListenerSocket) return;

	//Remote address
	TSharedRef<FInternetAddr> remoteAddress = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();

	bool pending;

	// handle incoming connection
	if (ListenerSocket->HasPendingConnection(pending) && pending)
	{
		// Already have a connection? destroy previous
		if (ConnectionSocket)
		{
			ConnectionSocket->Close();
			ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ConnectionSocket);
		}

		// New connection receive~!
		ConnectionSocket = ListenerSocket->Accept(*remoteAddress, TEXT("RamaTCP received socket connection"));

		if (ConnectionSocket != nullptr)
		{
			//Global cache of current remote address
			RemoteAddressForConnection = FIPv4Endpoint(remoteAddress);

			VShow("Accepted Connection! WHOOHO!!!");

			GetWorldTimerManager().SetTimer(_memberTimerHandle, this, &ASocketActor::TCPSocketListener, .01, true);
		}
	}
}

void ASocketActor::TCPSocketListener()
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

	VShow(FString::Printf(TEXT("Total Data read! %d"), receivedData.Num()).GetCharArray().GetData());

	const FString receivedUE4String = StringFromBinaryArray(receivedData);
	auto p = TEXT("As String!!! ~>") + receivedUE4String;
	VShow(p.GetCharArray().GetData());
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
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Networking.h"
#include "NetworkMessage.h"
#include "SocketActor.generated.h"

DEFINE_LOG_CATEGORY_STATIC(LogSocketCategory, Warning, All);
#define ScreenPrint(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, .0f, FColor::Red,text)
#define LogSocket(text) UE_LOG(LogSocketCategory, Warning, text)

UCLASS()
class CPPBASICSCENE_API ASocketActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASocketActor();
	virtual ~ASocketActor() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Destroyed() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere)
		UStaticMeshComponent *PickupMesh;

	UPROPERTY(EditAnywhere)
		USceneComponent *Root;

	// UFUNCTION()
	// void OnPlayerEnterBox(UPrimitiveComponent* overlappedComp, AActor*
	// otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool
	// bFromSweep, const FHitResult& sweepResult);

	FSocket *ListenerSocket;
	FSocket *ConnectionSocket;
	FIPv4Endpoint RemoteAddressForConnection;

	bool StartTCPReceiver(const FString &YourChosenSocketName,
		const FString &TheIp, const int32 ThePort);

	FSocket*
		CreateListenerSocket(const FString &YourChosenSocketName,
			const FString &TheIP, const int32 ThePort,
			const int32 receiveBufferSize = 2 * 1024 * 1024);

	//Timer functions, could be threads
	void Accept();	//can thread this eventually
	void Read();	//can thread this eventually

	//Format String IP4 to number array
	bool FormatIP4ToNumber(const FString& theIP, uint8(&Out)[4]);

	//Rama's StringFromBinaryArray
	const FString StringFromBinaryArray(TArray<uint8>& binaryArray);

private:

	FTimerHandle _listenerTimerHandle;
	FTimerHandle _receivedTimerHandle;


	inline void Print(const FString& text) {
		if (GEngine) 
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, text); 

		UE_LOG(LogSocketCategory, Warning, TEXT("%s"), *text);
	}

	void CloseSocket();
};

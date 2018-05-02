// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Networking.h"
#include "SocketActor.generated.h"

DEFINE_LOG_CATEGORY_STATIC(LogSocketFlag, Warning, All);
#define VShow(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red,text)
#define LogSocket(text) UE_LOG(LogSocketFlag, Warning, text)

UCLASS()
class CPPBASICSCENE_API ASocketActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASocketActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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
		CreateTCPConnectionListener(const FString &YourChosenSocketName,
			const FString &TheIP, const int32 ThePort,
			const int32 receiveBufferSize = 2 * 1024 * 1024);

	//Timer functions, could be threads
	void TCPConnectionListener();	//can thread this eventually
	void TCPSocketListener();	//can thread this eventually

	//Format String IP4 to number array
	bool FormatIP4ToNumber(const FString& theIP, uint8(&Out)[4]);

	//Rama's StringFromBinaryArray
	const FString StringFromBinaryArray(TArray<uint8>& binaryArray);

	FTimerHandle _memberTimerHandle;

	inline void Print(const FString& text) {
		if (GEngine) 
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, text); 

		UE_LOG(LogSocket, Warning, TEXT("%s"), text);
	}
};

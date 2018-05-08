// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ANetwork.generated.h"

UCLASS()
class ANetwork : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ANetwork();

	virtual ~ANetwork();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	static bool Connect();

	static bool Send(int8* data, int16 size, int32& sent);

	static void Recv();

	static void Close();

	static void EventLoop(void* data);

	static class FSocket* Socket;

	static bool Connected;

	static class FInternetAddr* InetAddr;
	class FNetworkRunnable* NetworkRunnable;

};

// Fill out your copyright notice in the Description page of Project Settings.

#include "FNetworkRunnable.h"
#include "RunnableThread.h"
#include "ANetwork.h"

FNetworkRunnable::FNetworkRunnable(ANetwork* InNetwork)
{
	Network = InNetwork;
	Thread = FRunnableThread::Create(this, TEXT("FNetworkRunnable"), 0, TPri_BelowNormal); //windows default = 8mb for thread, could specify more
																						   //
}

FNetworkRunnable::~FNetworkRunnable()
{
}

uint32 FNetworkRunnable::Run()
{
	Network->EventLoop(0);

	return 0;
}

void FNetworkRunnable::Exit()
{
	//Network->Close();
}
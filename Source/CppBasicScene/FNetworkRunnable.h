// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class CPPBASICSCENE_API FNetworkRunnable : FRunnable
{
public:
	FNetworkRunnable(class ANetwork* InNet);
	virtual ~FNetworkRunnable();

	virtual uint32 Run();

	virtual void Exit();

	FRunnableThread* Thread;

	class ANetwork* Network;
};
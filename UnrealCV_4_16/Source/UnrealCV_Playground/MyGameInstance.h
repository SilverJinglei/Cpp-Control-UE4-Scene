// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RoboticActor.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCV_PLAYGROUND_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
	
public:

	virtual bool ProcessConsoleExec(const TCHAR* Cmd, FOutputDevice& Ar, UObject* Executor) override;

	UFUNCTION(Exec)
	void GISay();

	UFUNCTION(Exec)
	void MotorOnForDegrees(FName robotName, int motorId, float degree, float speed);
};
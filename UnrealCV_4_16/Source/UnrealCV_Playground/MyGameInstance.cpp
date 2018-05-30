// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"

bool UMyGameInstance::ProcessConsoleExec(const TCHAR* Cmd, FOutputDevice& Ar, UObject* Executor)
{
	bool ret = Super::ProcessConsoleExec(Cmd, Ar, Executor);

	if (ret) return ret;

	for (AActor* actor : this->GetWorld()->GetCurrentLevel()->Actors)
	{
		if (actor)// && actor->IsA(ARoboticActor::StaticClass()))
		{
			auto hasResponse = actor->ProcessConsoleExec(Cmd, Ar, Executor);

			if (hasResponse)
				ret = true;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("--- Cmd:%s exec:%d"), Cmd, (int32)ret);
	return ret;
}

void UMyGameInstance::GISay()
{
	UE_LOG(LogTemp, Warning, TEXT("name:%s, Say hello"), *GetFName().ToString());
}

void UMyGameInstance::MotorOnForDegrees(FName robotName, int motorId, float degree, float speed)
{
	for (AActor* actor : this->GetWorld()->GetCurrentLevel()->Actors)
	{
		bool isTargetRobot = actor && actor->IsA(ARoboticActor::StaticClass()) && actor->GetFName().IsEqual(robotName);
		if (!isTargetRobot)
			continue;

		ARoboticActor* robot = Cast<ARoboticActor>(actor);

		UE_LOG(LogTemp, Warning, TEXT("--- %s 's Motors Count:%d"), *robot->GetFName().ToString(), robot->Motors.Num());

		if(robot->Motors.Num() > 0)
			robot->Motors[motorId]->SetTargetDegrees(degree, speed);
	}
}

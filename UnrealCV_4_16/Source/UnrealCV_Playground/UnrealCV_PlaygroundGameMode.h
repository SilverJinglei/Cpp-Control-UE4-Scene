// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UnrealCV_PlaygroundGameMode.generated.h"

UCLASS(minimalapi)
class AUnrealCV_PlaygroundGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AUnrealCV_PlaygroundGameMode();

	UFUNCTION(Exec)
	virtual void solname(FString _str, int32 _num);
};




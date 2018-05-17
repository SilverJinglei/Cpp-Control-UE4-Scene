// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UnrealCV_PlaygroundHUD.generated.h"

UCLASS()
class AUnrealCV_PlaygroundHUD : public AHUD
{
	GENERATED_BODY()

public:
	AUnrealCV_PlaygroundHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};


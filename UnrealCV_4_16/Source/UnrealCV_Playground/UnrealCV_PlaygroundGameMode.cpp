// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "UnrealCV_PlaygroundGameMode.h"
#include "UnrealCV_PlaygroundHUD.h"
#include "UnrealCV_PlaygroundCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUnrealCV_PlaygroundGameMode::AUnrealCV_PlaygroundGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AUnrealCV_PlaygroundHUD::StaticClass();
}

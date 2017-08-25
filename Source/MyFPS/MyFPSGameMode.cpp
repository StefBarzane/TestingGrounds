// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "MyFPS.h"
#include "MyFPSGameMode.h"
#include "MyFPSHUD.h"
#include "Player/MyFPSCharacter.h"

AMyFPSGameMode::AMyFPSGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Dynamic/Character/Behaviour/BP_Character"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AMyFPSHUD::StaticClass();
}

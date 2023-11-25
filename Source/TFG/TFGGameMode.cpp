// Copyright Epic Games, Inc. All Rights Reserved.

#include "TFGGameMode.h"
#include "TFGCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATFGGameMode::ATFGGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Blueprints/BP_Monster_Basic"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}

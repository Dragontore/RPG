// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "RPGGameMode.h"
#include "RPGCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARPGGameMode::ARPGGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Base_Hold/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "Automate69kGameMode.h"
#include "Automate69kCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAutomate69kGameMode::AAutomate69kGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

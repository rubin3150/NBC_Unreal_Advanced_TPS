// Copyright Epic Games, Inc. All Rights Reserved.

#include "Unreal_Advanced_TPSGameMode.h"
#include "Unreal_Advanced_TPSCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUnreal_Advanced_TPSGameMode::AUnreal_Advanced_TPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

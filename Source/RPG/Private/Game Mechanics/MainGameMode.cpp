// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"

#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

#include "TargetPoints/RespawnPoints.h"

AMainGameMode::AMainGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClass(TEXT("/Game/Blueprints/Characters/Base_Character/BP_BaseCharacter"));
	if (PlayerPawnClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnClass.Class;
	}
	SpawnPoint = FVector(-400.0f, 50.0f, 2000.f);
}

void AMainGameMode::SetRespawnLocation(FVector respawnLocation)
{
	if (Role < ROLE_Authority)
	{
		ServerSetRespawnLocation(respawnLocation);
	}
	else if (Role == ROLE_Authority)
	{

		SpawnPoint = respawnLocation;
	}
}

bool AMainGameMode::ServerSetRespawnLocation_Validate(FVector serverRespawnLocation)
{
	return true;
}

void AMainGameMode::ServerSetRespawnLocation_Implementation(FVector serverRespawnLocation)
{
	if (Role == ROLE_Authority)
	{
		SetRespawnLocation(serverRespawnLocation);
	}
}

void AMainGameMode::Respawn(AController* Controller)
{
	if (Controller)
	{
		if (Role == ROLE_Authority)
		{
			//TODO Set Respawn point to Target Points

			FVector Location = FVector(-400.0f, 50.0f, 2000.f);
			if (APawn* Pawn = GetWorld()->SpawnActor<APawn>(DefaultPawnClass, SpawnPoint, FRotator::ZeroRotator))
			{
				Controller->Possess(Pawn);
			}
		}
	}
}

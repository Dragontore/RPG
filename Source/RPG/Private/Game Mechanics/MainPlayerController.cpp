// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"

#include "Engine/World.h"
#include "Engine/Engine.h"
#include "TimerManager.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"

AMainPlayerController::AMainPlayerController()
{

}

void AMainPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMainPlayerController, SpawnPoint);
}

void AMainPlayerController::SetRespawnLocation(FVector respawnLocation)
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

FVector AMainPlayerController::GetSpawnPoint()
{
	return SpawnPoint;
}

void AMainPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AMainPlayerController::ServerSetRespawnLocation_Validate(FVector aerverRespawnLocation)
{
	return true;
}

void AMainPlayerController::ServerSetRespawnLocation_Implementation(FVector serverRespawnLocation)
{
	if (Role == ROLE_Authority)
	{
		SetRespawnLocation(serverRespawnLocation);

	}
}

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SpawnPoint = FVector(-680.f, -350.f, 140.f);
}

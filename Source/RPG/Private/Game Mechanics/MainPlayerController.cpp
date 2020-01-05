// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"

#include "Engine/World.h"
#include "Engine/Engine.h"
#include "TimerManager.h"
#include "Net/UnrealNetwork.h"

AMainPlayerController::AMainPlayerController()
{
	SpawnPoint = FVector(-840.0f, -150.0f, 405.0f);
}

void AMainPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(AMainPlayerController, SpawnPoint, COND_OwnerOnly);
}

void AMainPlayerController::SetRespawnLocation(FVector respawnLocation)
{
	UE_LOG(LogTemp, Warning, TEXT("Set Spawn Point"))
		if (Role < ROLE_Authority)
		{
			ClientSetRespawnLocation(respawnLocation);
		}
		else if (Role == ROLE_Authority)
		{

			SpawnPoint = respawnLocation;
		}
}

bool AMainPlayerController::ClientSetRespawnLocation_Validate(FVector clientRespawnLocation)
{
	return true;
}

void AMainPlayerController::ClientSetRespawnLocation_Implementation(FVector clientRespawnLocation)
{
	if (Role == ROLE_Authority)
	{
		SetRespawnLocation(clientRespawnLocation);
	}
}
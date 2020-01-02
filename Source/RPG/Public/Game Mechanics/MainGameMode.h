// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API AMainGameMode : public AGameMode
{
	GENERATED_BODY()

public: 
	AMainGameMode();

	void SetRespawnLocation(FVector respawnLocation);

protected:

	FVector SpawnPoint;

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSetRespawnLocation(FVector serverRespawnLocation);
	bool ServerSetRespawnLocation_Validate(FVector serverRespawnLocation);
	void ServerSetRespawnLocation_Implementation(FVector serverRespawnLocation);

public:

	void Respawn(AController* Controller);
	
};

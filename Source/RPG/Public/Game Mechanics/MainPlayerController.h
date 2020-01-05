// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

		AMainPlayerController();
		
public:

	UPROPERTY(Replicated)
	FVector SpawnPoint;

	UFUNCTION()
	void SetRespawnLocation(FVector respawnLocation);

protected:

	UFUNCTION(Client, Reliable, WithValidation)
	void ClientSetRespawnLocation(FVector clientRespawnLocation);
	bool ClientSetRespawnLocation_Validate(FVector clientRespawnLocation);
	void ClientSetRespawnLocation_Implementation(FVector clientRespawnLocation);
	
};

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

	UPROPERTY(Replicated)
	bool SpawnPointSet;

	UFUNCTION()
	void SetRespawnLocation(FVector respawnLocation);

	UFUNCTION(BlueprintCallable, Category = "Getter")
	FVector GetSpawnPoint();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSetRespawnLocation(FVector serverRespawnLocation);
	bool ServerSetRespawnLocation_Validate(FVector serverRespawnLocation);
	void ServerSetRespawnLocation_Implementation(FVector serverRespawnLocation);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};

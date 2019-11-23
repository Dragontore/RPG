// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseStatsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_API UBaseStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:

protected:

	FTimerHandle TimerHandle;

	UPROPERTY(Replicated)
	float CurrentHealth;

	UPROPERTY(Replicated)
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStats")
	float RegenRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStats")
	float HealthRegenRate;

	

public:	
	// Sets default values for this component's properties
	UBaseStatsComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//Handles the bas Stats regen
	void HandleBaseStats();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerHealthRegen(float serverHealthRegen);
	bool ServerHealthRegen_Validate(float serverHealthRegen);
	void ServerHealthRegen_Implementation(float serverHealthRegen);

public:	

	void HealthRegen(float healthRegen);
	
};

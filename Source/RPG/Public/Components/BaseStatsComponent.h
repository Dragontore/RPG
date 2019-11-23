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

	// Health Varibles
	UPROPERTY(Replicated)
	float CurrentHealth;

	UPROPERTY(Replicated)
	float MaxHealth;

	float HealthRegenRate;

	//Stamina Varibles
	UPROPERTY(Replicated)
	float CurrentStamina;

	UPROPERTY(Replicated)
	float MaxStamina;

	float StaminaRegenRate;

	//Regenratiion rate for all stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStats")
	float RegenRate;

	

public:	
	// Sets default values for this component's properties
	UBaseStatsComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//Handles the base Stats regen
	void HandleBaseStats();

	// Health Stamina Functions
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerHealthRegen(float serverHealthRegen);
	bool ServerHealthRegen_Validate(float serverHealthRegen);
	void ServerHealthRegen_Implementation(float serverHealthRegen);

	//Stamina Server Functions
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerStaminaRegen(float serverStaminaRegen);
	bool ServerStaminaRegen_Validate(float serverStaminaRegen);
	void ServerStaminaRegen_Implementation(float serverStaminaRegen);

public:	
	// Non Server Health Function
	void HealthRegen(float healthRegen);
	// Non Server Stamina Function
	void StaminaRegen(float StaminaRegen);

	// Health Getter Function
	UFUNCTION(BlueprintCallable, Category = "Getter")
	float GetCurrentHealth();
	
	UFUNCTION(BlueprintCallable, Category = "Getter")
	float GetMaxHealth();

	// Stamina Getter Function
	UFUNCTION(BlueprintCallable, Category = "Getter")
	float GetCurrentStamina();

	UFUNCTION(BlueprintCallable, Category = "Getter")
	float GetMaxStamina();



};

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

	float HealthIncreaseRate;

	//Stamina Varibles
	UPROPERTY(Replicated)
	float CurrentStamina;

	UPROPERTY(Replicated)
	float MaxStamina;

	float StaminaIncreaseRate;

	//Mana Varibles
	UPROPERTY(Replicated)
	float CurrentMana;

	UPROPERTY(Replicated)
	float MaxMana;

	float ManaIncreaseRate;

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

	// Health Server Functions
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerIncreaseCurrentHealth(float serverCurrentHealthIncrease);
	bool ServerIncreaseCurrentHealth_Validate(float serverCurrentHealthIncrease);
	void ServerIncreaseCurrentHealth_Implementation(float serverCurrentHealthIncrease);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerDecreaseCurrentHealth(float serverCurrentHealthDecrease);
	bool ServerDecreaseCurrentHealth_Validate(float serverCurrentHealthDecrease);
	void ServerDecreaseCurrentHealth_Implementation(float serverCurrentHealthDecrease);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerIncreaseMaxHealth(float serverMaxHealthIncrease);
	bool ServerIncreaseMaxHealth_Validate(float serverMaxHealthIncrease);
	void ServerIncreaseMaxHealth_Implementation(float serverMaxHealthIncrease);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerDecreaseMaxHealth(float serverMaxHealthDecrease);
	bool ServerDecreaseMaxHealth_Validate(float serverMaxHealthDecrease);
	void ServerDecreaseMaxHealth_Implementation(float serverMaxHealthDecrease);

	//Stamina Server Functions
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerIncreaseCurrentStamina(float serverCurrentStaminaIncrease);
	bool ServerIncreaseCurrentStamina_Validate(float serverCurrentStaminaIncrease);
	void ServerIncreaseCurrentStamina_Implementation(float serverCurrentStaminaIncrease);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerDecreaseCurrentStamina(float serverCurrentStaminaDecrease);
	bool ServerDecreaseCurrentStamina_Validate(float serverCurrentStaminaDecrease);
	void ServerDecreaseCurrentStamina_Implementation(float serverCurrentSaminaDecrease);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerIncreaseMaxStamina(float serverMaxStaminaIncrease);
	bool ServerIncreaseMaxStamina_Validate(float serverMaxStaminaIncrease);
	void ServerIncreaseMaxStamina_Implementation(float serverMaxStaminaIncrease);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerDecreaseMaxStamina(float serverMaxStaminaDecrease);
	bool ServerDecreaseMaxStamina_Validate(float serverMaxStaminaDecrease);
	void ServerDecreaseMaxStamina_Implementation(float serverMaxStaminaDecrease);

	//Mana Server Function
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerIncreaseCurrentMana(float serverCurrentManaIncrease);
	bool ServerIncreaseCurrentMana_Validate(float serverCurrentManaIncrease);
	void ServerIncreaseCurrentMana_Implementation(float serverCurrentManaIncrease);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerDecreaseCurrentMana(float serverCurrentManaDecrease);
	bool ServerDecreaseCurrentMana_Validate(float serverCurrentManaDecrease);
	void ServerDecreaseCurrentMana_Implementation(float serverCurrentManaDecrease);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerIncreaseMaxMana(float serverMaxManaIncrease);
	bool ServerIncreaseMaxMana_Validate(float serverMaxManaIncrease);
	void ServerIncreaseMaxMana_Implementation(float serverMaxManaIncrease);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerDecreaseMaxMana(float serverMaxManaDecrease);
	bool ServerDecreaseMaxMana_Validate(float serverMaxManaDecrease);
	void ServerDecreaseMaxMana_Implementation(float serverMaxManaDecrease);

public:	

	// Non Server Health Function
	void IncreaseCurrentHealth(float healthIncrease);
	void IncreaseMaxHealth(float healthIncrease);
	void DecreaseCurrentHealth(float healthDecrease);
	void DecreaseMaxHealth(float healthDecrease);
	// Non Server Stamina Function
	void IncreaseCurrentStamina(float StaminaIncrease);
	void IncreaseMaxStamina(float StaminaIncrease);
	void DecreaseCurrentStamina(float StaminaDecrease);
	void DecreaseMaxStamina(float StaminaDecrease);
	// Non Server Mana Function
	void IncreaseCurrentMana(float ManaIncrease);
	void IncreaseMaxMana(float ManaIncrease);
	void DecreaseCurrentMana(float ManaDecrease);
	void DecreaseMaxMana(float ManaDecrease);

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

	//Mana Getter Function
	UFUNCTION(BlueprintCallable, Category = "Getter")
	float GetCurrentMana();

	UFUNCTION(BlueprintCallable, Category = "Getter")
	float GetMaxMana();

};

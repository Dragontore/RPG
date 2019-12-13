// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseStatsComponent.generated.h"

class ABaseCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_API UBaseStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:

protected:

	FTimerHandle HealthTimerHandle;
	FTimerHandle StaminaTimerHandle;
	FTimerHandle ManaTimerHandle;


	// Health Varibles
	UPROPERTY(Replicated)
	float CurrentHealth;

	UPROPERTY(Replicated)
	float MaxHealth;

	float HealthIncreaseRate;
	float HealthDecreaseRate;

	//Stamina Varibles
	UPROPERTY(Replicated)
	float CurrentStamina;

	UPROPERTY(Replicated)
	float MaxStamina;

	float StaminaIncreaseRate;
	float StaminaDecreaseRate;

	//Mana Varibles
	UPROPERTY(Replicated)
	float CurrentMana;

	UPROPERTY(Replicated)
	float MaxMana;

	float ManaIncreaseRate;
	float ManaDecreaseRate;

	//Regenratiion rate for Health stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStats")
	float HealthRegenRate;

	//Regenratiion rate for Health stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStats")
	float StaminaRegenRate;

	//Regenratiion rate for Health stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseStats")
	float ManaRegenRate;

	ABaseCharacter* BaseCharacter;

	//Base Stats

	UPROPERTY(Replicated)
	float Strength;

	UPROPERTY(Replicated)
	float Charm;

	UPROPERTY(Replicated)
	float Perception;

	UPROPERTY(Replicated)
	float Bravery;

	UPROPERTY(Replicated)
	float Endurance;

	UPROPERTY(Replicated)
	float Agility;

	//TODO Add follow Base Stats
	//Stealth
	//Intellgence
	//Luck

public:	
	// Sets default values for this component's properties
	UBaseStatsComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void SetTimers();

	//Handles the Health Stats regen/Degen
	void HandleIncreaseHealthStats();
	void HandleDecreaseHealthStats();

	//Handles the Stamina Stats Regen/Degen
	void HandleIncreaseStaminaStats();
	void HandleDecreaseStaminaStats();

	//Handle the Mana Stats Regen/Degen
	void HandleIncreaseManaStats();
	void HandleDecreaseManaStats();

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

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerIncreaseHealthRegen(float serverHealthRegenIncrease);
	bool ServerIncreaseHealthRegen_Validate(float serverHealthRegenIncrease);
	void ServerIncreaseHealthRegen_Implementation(float serverHealthRegenIncrease);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerDecreaseHealthRegen(float serverHealthRegenDecrease);
	bool ServerDecreaseHealthRegen_Validate(float serverHealthRegenDecrease);
	void ServerDecreaseHealthRegen_Implementation(float serverHealthDecrease);

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

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerIncreaseStaminaRegen(float serverStaminaRegenIncrease);
	bool ServerIncreaseStaminaRegen_Validate(float serverStaminaRegenIncrease);
	void ServerIncreaseStaminaRegen_Implementation(float serverStaminaRegenIncrease);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerDecreaseStaminaRegen(float serverStaminaRegenDecrease);
	bool ServerDecreaseStaminaRegen_Validate(float serverStaminaRegenDecrease);
	void ServerDecreaseStaminaRegen_Implementation(float serverStaminaRegenDecrease);

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

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerIncreaseManaRegen(float serverManaRegenIncrease);
	bool ServerIncreaseManaRegen_Validate(float serverManaRegenIncrease);
	void ServerIncreaseManaRegen_Implementation(float serverManaRegenIncrease);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerDecreaseManaRegen(float serverManaRegenDecrease);
	bool ServerDecreaseManaRegen_Validate(float serverManaRegenDecrease);
	void ServerDecreaseManaRegen_Implementation(float serverManaRegenDecrease);

	// Server Sprint Function

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerControlSprintingTimer(bool IsSprinting);
	bool ServerControlSprintingTimer_Validate(bool IsSprinting);
	void ServerControlSprintingTimer_Implementation(bool IsSprinting);

	// Server Base Stats Increase Function

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerIncreaseStrength(float serverStrenthIncrease);
	bool ServerIncreaseStrength_Validate(float serverStrengthIncrease);
	void ServerIncreaseStrength_Implementation(float serverStrengthIncrease);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerIncreaseCharm(float serverCharmIncrease);
	bool ServerIncreaseCharm_Validate(float serverCharmIncrease);
	void ServerIncreaseCharm_Implementation(float serverCharmIncrease);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerIncreasePerception(float serverPerceptionIncrease);
	bool ServerIncreasePerception_Validate(float serverPerceptionIncrease);
	void ServerIncreasePerception_Implementation(float serverPerceptionIncrease);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerIncreaseBravery(float serverBraveryIncrease);
	bool ServerIncreaseBravery_Validate(float serverBraveryIncrease);
	void ServerIncreaseBravery_Implementation(float serverBraveryIncrease);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerIncreaseEndurance(float serverEnduranceIncrease);
	bool ServerIncreaseEndurance_Validate(float serverEnduranceIncrease);
	void ServerIncreaseEndurance_Implementation(float serverEnduranceIncrease);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerIncreaseAgility(float serverAgilityIncrease);
	bool ServerIncreaseAgility_Validate(float serverAgilityIncrease);
	void ServerIncreaseAgility_Implementation(float serverAgilityIncrease);

	// Server Base Stats Decrease Function

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerDecreaseStrength(float serverStrenthDecrease);
	bool ServerDecreaseStrength_Validate(float serverStrengtDecrease);
	void ServerDecreaseStrength_Implementation(float serverStrengthDecrease);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerDecreaseCharm(float serverCharmDecrease);
	bool ServerDecreaseCharm_Validate(float serverCharmDecrease);
	void ServerDecreaseCharm_Implementation(float serverCharmDecrease);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerDecreasePerception(float serverPerceptionDecrease);
	bool ServerDecreasePerception_Validate(float serverPerceptionDecrease);
	void ServerDecreasePerception_Implementation(float serverPerceptionDecrease);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerDecreaseBravery(float serverBraveryDecrease);
	bool ServerDecreaseBravery_Validate(float serverBraveryDecrease);
	void ServerDecreaseBravery_Implementation(float serverBraveryDecrease);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerDecreaseEndurance(float serverEnduranceDecrease);
	bool ServerDecreaseEndurance_Validate(float serverEnduranceDecrease);
	void ServerDecreaseEndurance_Implementation(float serverEnduranceDecrease);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerDecreaseAgility(float serverAgilityDecrease);
	bool ServerDecreaseAgility_Validate(float serverAgilityDecrease);
	void ServerDecreaseAgility_Implementation(float serverAgilityDecrease);

public:	

	// Non Server Health Function
	void IncreaseCurrentHealth(float healthIncrease);
	void IncreaseMaxHealth(float healthIncrease);
	void IncreaseHealthRegenRate(float healthRegenIncrease);
	void DecreaseCurrentHealth(float healthDecrease);
	void DecreaseMaxHealth(float healthDecrease);
	void DecreaseHealthRegenRate(float healthRegenDecrease);
	// Non Server Stamina Function
	void IncreaseCurrentStamina(float StaminaIncrease);
	void IncreaseMaxStamina(float StaminaIncrease);
	void IncreaseStaminaRegenRate(float staminaRegenIncrease);
	void DecreaseCurrentStamina(float StaminaDecrease);
	void DecreaseMaxStamina(float StaminaDecrease);
	void DecreaseStaminaRegenRate(float staminaRegenDecrease);
	// Non Server Mana Function
	void IncreaseCurrentMana(float ManaIncrease);
	void IncreaseMaxMana(float ManaIncrease);
	void IncreaseManaRegenRate(float manaRegenIncrease);
	void DecreaseCurrentMana(float ManaDecrease);
	void DecreaseMaxMana(float ManaDecrease);
	void DecreaseManaRegenRate(float manaRegenDecrease);

	//Non Server Increase Base Stat Function
	void IncreaseStrength(float increaseStrength);
	void IncreaseCharm(float increaseCharm);
	void IncreasePerception(float increasePerception);
	void IncreaseBravery(float increaseBravery);
	void IncreaseEndurance(float increaseEndurance);
	void IncreaseAgility(float increaseAgility);

	//Non Server Decrease Base Stat Function
	void DecreaseStrength(float decreaseStrength);
	void DecreaseCharm(float decreaseCharm);
	void DecreasePerception(float decreasePerception);
	void DecreaseBravery(float decreaseBravery);
	void DecreaseEndurance(float decreaseEndurance);
	void DecreaseAgility(float decreaseAgility);


	// Health Getter Function
	UFUNCTION(BlueprintCallable, Category = "Health Getter")
	float GetCurrentHealth();
	
	UFUNCTION(BlueprintCallable, Category = "Health Getter")
	float GetMaxHealth();

	UFUNCTION(BlueprintCallable, Category = "Health Getter")
	float GetHealthRegenRate();

	// Stamina Getter Function
	UFUNCTION(BlueprintCallable, Category = "StaminaGetter")
	float GetCurrentStamina();

	UFUNCTION(BlueprintCallable, Category = "Stamina Getter")
	float GetMaxStamina();

	UFUNCTION(BlueprintCallable, Category = "Stamina Getter")
	float GetStaminaRegenRate();

	//Mana Getter Function
	UFUNCTION(BlueprintCallable, Category = "Mana Getter")
	float GetCurrentMana();

	UFUNCTION(BlueprintCallable, Category = "Mana Getter")
	float GetMaxMana();

	UFUNCTION(BlueprintCallable, Category = "Mana Getter")
	float GetManaRegenRate();

	// Base Stats Getter Functions
	UFUNCTION(BlueprintCallable, Category = "Getter")
	float GetStrength();

	UFUNCTION(BlueprintCallable, Category = "Getter")
	float GetCharm();

	UFUNCTION(BlueprintCallable, Category = "Getter")
	float GetPerception();

	UFUNCTION(BlueprintCallable, Category = "Getter")
	float GetBravery();

	UFUNCTION(BlueprintCallable, Category = "Getter")
	float GetEndurance();

	UFUNCTION(BlueprintCallable, Category = "Getter")
	float GetAgility();

	//Character Functions

	void ControlSprintingTimer(bool IsSprinting);
};

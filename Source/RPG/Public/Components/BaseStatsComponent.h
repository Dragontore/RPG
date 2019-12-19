// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseStatsComponent.generated.h"

class ABaseCharacter;
class USphereComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_API UBaseStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	//Collison Sphere Setting
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collison")
	USphereComponent* CollisonSphere;

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

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Collison")
	float CollisonRadius;

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

	UPROPERTY(Replicated)
	float Stealth;

	UPROPERTY(Replicated)
	float Intelligence;

	UPROPERTY(Replicated)
	float Luck;

	UPROPERTY(Replicated)
	float UnarmedCombat;

	UPROPERTY(Replicated)
	int BronzeCoin;

	UPROPERTY(Replicated)
	int SilverCoin;

	UPROPERTY(Replicated)
	int GoldCoin;

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

	//Server Coin Functions

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerIncreaseBronzeCoins(float serverBronzeCoinIncrease);
	bool ServerIncreaseBronzeCoins_Validate(float serverBronzeCoinIncrease);
	void ServerIncreaseBronzeCoins_Implementation(float serverBronzeCoinIncrease);
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerDecreaseBronzeCoins(float serverBronzeCoinDecrease);
	bool ServerDecreaseBronzeCoins_Validate(float serverBronzeCoinDecrease);
	void ServerDecreaseBronzeCoins_Implementation(float serverBronzeCoinDecrease);
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerIncreaseSilverCoins(float serverSilverCoinIncrease);
	bool ServerIncreaseSilverCoins_Validate(float serverSilverCoinIncrease);
	void ServerIncreaseSilverCoins_Implementation(float serverSilverCoinIncrease);
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerDecreaseSilverCoins(float serverSilverCoinDecrease);
	bool ServerDecreaseSilverCoins_Validate(float serverSilverCoinDecrease);
	void ServerDecreaseSilverCoins_Implementation(float serverSilverCoinDecrease);
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerIncreaseGoldCoins(float serverGoldCoinIncrease);
	bool ServerIncreaseGoldCoins_Validate(float serverGoldCoinIncrease);
	void ServerIncreaseGoldCoins_Implementation(float serverGoldCoinIncrease);
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerDecreaseGoldCoins(float serverGoldCoinDecrease);
	bool ServerDecreaseGoldCoins_Validate(float serverGoldCoinDecrease);
	void ServerDecreaseGoldCoins_Implementation(float serverGoldCoinDecrease);

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

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerIncreaseStealth(float serverStealthIncrease);
	bool ServerIncreaseStealth_Validate(float serverStealthIncrease);
	void ServerIncreaseStealth_Implementation(float serverStealthIncrease);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerIncreaseIntelligence(float serverIntelligenceIncrease);
	bool ServerIncreaseIntelligence_Validate(float serverIntelligenceIncrease);
	void ServerIncreaseIntelligence_Implementation(float serverIntelligenceIncrease);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerIncreaseLuck(float serverLuckIncrease);
	bool ServerIncreaseLuck_Validate(float serverLuckIncrease);
	void ServerIncreaseLuck_Implementation(float serverLuckIncrease);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerIncreaseUnarmedCombat(float serverUnarmedCombatIncrease);
	bool ServerIncreaseUnarmedCombat_Validate(float serverUnarmedCombatIncrease);
	void ServerIncreaseUnarmedCombat_Implementation(float serverUnarmedCombatIncrease);

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

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerDecreaseStealth(float serverStealthDecrease);
	bool ServerDecreaseStealth_Validate(float serverStealthDecrease);
	void ServerDecreaseStealth_Implementation(float serverStealthDecrease);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerDecreaseIntelligence(float serverIntelligenceDecrease);
	bool ServerDecreaseIntelligence_Validate(float serverIntelligenceDecrease);
	void ServerDecreaseIntelligence_Implementation(float serverIntelligenceDecrease);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerDecreaseLuck(float serverLuckDecrease);
	bool ServerDecreaseLuck_Validate(float serverLuckDecrease);
	void ServerDecreaseLuck_Implementation(float serverLuckDecrease);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerDecreaseUnarmedCombat(float serverUnarmedCombatDecrease);
	bool ServerDecreaseUnarmedCombat_Validate(float serverUnarmedCombatDecrease);
	void ServerDecreaseUnarmedCombat_Implementation(float serverUnarmedCombatDecrease);

	// Collison Radius Server Functions
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerIncreaseCollisonRadius(float serverIncreaseCollisonRadius);
	bool ServerIncreaseCollisonRadius_Validate(float serverIncreaseCollisonRadius);
	void ServerIncreaseCollisonRadius_Implementation(float serverIncreaseCollisonRadius);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerDecreaseCollisonRadius(float serverDecreaseCollisonRadius);
	bool ServerDecreaseCollisonRadius_Validate(float serverDecreaseCollisonRadius);
	void ServerDecreaseCollisonRadius_Implementation(float serverDecreaseCollisonRadius);

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
	void IncreaseStealth(float increaseStealth);
	void IncreaseIntelligence(float increaseIntelligence);
	void IncreaseLuck(float increaseLuck);
	void IncreaseUnarmedCombat(float increaseUnarmedCombat);
	//Non Server Decrease Base Stat Function
	void DecreaseStrength(float decreaseStrength);
	void DecreaseCharm(float decreaseCharm);
	void DecreasePerception(float decreasePerception);
	void DecreaseBravery(float decreaseBravery);
	void DecreaseEndurance(float decreaseEndurance);
	void DecreaseAgility(float decreaseAgility);
	void DecreaseStealth(float decreaseStealth);
	void DecreaseIntelligence(float decreaseIntelligence);
	void DecreaseLuck(float decreaseLuck);
	void DecreaseUnarmedCombat(float decreaseUnarmedCombat);
	// Non Server Collison Functions
	UFUNCTION(BlueprintCallable, Category = "Collison")
	float GetCollisonRadius();
	UFUNCTION(BlueprintCallable, Category = "Collison")
	void IncreaseCollisonRadius(float IncreaseCollisonRadius);
	UFUNCTION(BlueprintCallable, Category = "Collison")
	void DecreaseCollisonRadius(float decreaseCollisonRadius);
	//Non Server Coin Function
	void IncreaseBronzeCoins(float increaseBronzeCoin);
	void IncreaseSilverCoins(float increaseSilverCoin);
	void IncreaseGoldCoins(float increaseGoldCoin);
	void DecreaseBronzeCoins(float decreaseBronzeCoin);
	void DecreaseSilverCoins(float decreaseSilverCoin);
	void DecreaseGoldCoins(float decreaseGoldCoin);

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
	UFUNCTION(BlueprintCallable, Category = "Getter")
	float GetStealth();
	UFUNCTION(BlueprintCallable, Category = "Getter")
	float GetIntelligence();
	UFUNCTION(BlueprintCallable, Category = "Getter")
	float GetLuck();
	UFUNCTION(BlueprintCallable, Category = "Getter")
	float GetUnarmedCombat();

	//Coin Getter Function
	UFUNCTION(BlueprintCallable, Category = "Coin Getter")
	float GetBronzeCoins();
	UFUNCTION(BlueprintCallable, Category = "Coin Getter")
	float GetSilverCoins();
	UFUNCTION(BlueprintCallable, Category = "Coin Getter")
	float GetGoldCoins();

	//Character Functions

	void ControlSprintingTimer(bool IsSprinting);
};

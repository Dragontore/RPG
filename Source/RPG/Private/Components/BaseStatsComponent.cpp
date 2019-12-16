// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseStatsComponent.h"

#include "Net/UnrealNetwork.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "TimerManager.h"
#include "Components/SphereComponent.h"

#include "Character/BaseCharacter.h"



// Sets default values for this component's properties
UBaseStatsComponent::UBaseStatsComponent()
{

	// Collison Sphere Radius
	CollisonRadius = 150.f;

	// Collison Sphere
	CollisonSphere = CreateDefaultSubobject<USphereComponent>("Collison Sphere");
	CollisonSphere->SetSphereRadius(CollisonRadius);

	//Health defaults
	CurrentHealth = 100.f;
	MaxHealth = 100.f;
	HealthIncreaseRate = 5.f;
	HealthDecreaseRate = 5.f;

	//Stamina Defaults
	CurrentStamina = 100.f;
	MaxStamina = 100.f;
	StaminaIncreaseRate = 5.f;
	StaminaDecreaseRate = 5.f;

	// Mana Defaults
	CurrentMana = 100.f;
	MaxMana = 100.f;
	ManaIncreaseRate = 5.f;
	ManaDecreaseRate = 5.f;

	HealthRegenRate = 1.f;
	StaminaRegenRate = 1.f;
	ManaRegenRate = 1.f;

	BaseCharacter = Cast<ABaseCharacter>(GetOwner());

	// Base State Starting Defaults
	Strength = 1.f;
	Charm = 1.f;
	Perception = 1.f;
	Bravery = 1.f;
	Endurance = 1.f;
	Agility = 1.f;
	Stealth = 1.f;
	Intelligence = 1.f;
	Luck = 1.f;
	UnarmedCombat = 1.f;

	//Coin Defaults
	BronzeCoin = 10;
	SilverCoin = 0;
	GoldCoin = 0;
}


// Called when the game starts
void UBaseStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	SetIsReplicated(true);

	SetTimers();

	//TODO Set Function to set base Stats on game start.
}

void UBaseStatsComponent::SetTimers()
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		GetWorld()->GetTimerManager().SetTimer(HealthTimerHandle, this, &UBaseStatsComponent::HandleIncreaseHealthStats, HealthRegenRate, true);
		GetWorld()->GetTimerManager().SetTimer(StaminaTimerHandle, this, &UBaseStatsComponent::HandleIncreaseStaminaStats, StaminaRegenRate, true);
		GetWorld()->GetTimerManager().SetTimer(ManaTimerHandle, this, &UBaseStatsComponent::HandleIncreaseManaStats, ManaRegenRate, true);
	}
}

void UBaseStatsComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate to every client, no special condition required
	// Health Replicated Varibles
	DOREPLIFETIME(UBaseStatsComponent, CurrentHealth);
	DOREPLIFETIME(UBaseStatsComponent, MaxHealth);

	//Stamina Replicated Varibles
	DOREPLIFETIME(UBaseStatsComponent, CurrentStamina);
	DOREPLIFETIME(UBaseStatsComponent, MaxStamina);

	//Mana Replicated Varibles
	DOREPLIFETIME(UBaseStatsComponent, CurrentMana);
	DOREPLIFETIME(UBaseStatsComponent, MaxMana);

	// Base Stats Varibles
	DOREPLIFETIME(UBaseStatsComponent, Strength);
	DOREPLIFETIME(UBaseStatsComponent, Charm);
	DOREPLIFETIME(UBaseStatsComponent, Perception);
	DOREPLIFETIME(UBaseStatsComponent, Bravery);
	DOREPLIFETIME(UBaseStatsComponent, Endurance);
	DOREPLIFETIME(UBaseStatsComponent, Agility);
	DOREPLIFETIME(UBaseStatsComponent, Stealth);
	DOREPLIFETIME(UBaseStatsComponent, Intelligence);
	DOREPLIFETIME(UBaseStatsComponent, Luck);
	DOREPLIFETIME(UBaseStatsComponent, UnarmedCombat);

	// Collison Varibles
	DOREPLIFETIME(UBaseStatsComponent, CollisonRadius);

	// Coin Varibles
	DOREPLIFETIME(UBaseStatsComponent, BronzeCoin);
	DOREPLIFETIME(UBaseStatsComponent, SilverCoin);
	DOREPLIFETIME(UBaseStatsComponent, GoldCoin);

}

void UBaseStatsComponent::HandleIncreaseHealthStats()
{
	IncreaseCurrentHealth(HealthIncreaseRate);
}

void UBaseStatsComponent::HandleDecreaseHealthStats()
{
	DecreaseCurrentHealth(HealthDecreaseRate);
}

void UBaseStatsComponent::HandleIncreaseStaminaStats()
{
	IncreaseCurrentStamina(StaminaIncreaseRate);
}

void UBaseStatsComponent::HandleDecreaseStaminaStats()
{
	DecreaseCurrentStamina(StaminaDecreaseRate);
}

void UBaseStatsComponent::HandleIncreaseManaStats()
{
	IncreaseCurrentMana(ManaIncreaseRate);
}

void UBaseStatsComponent::HandleDecreaseManaStats()
{
	DecreaseCurrentMana(ManaDecreaseRate);
}

void UBaseStatsComponent::IncreaseCurrentHealth(float healthIncrease)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerIncreaseCurrentHealth(healthIncrease);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{

		if (CurrentHealth >= MaxHealth)
		{
			CurrentHealth = MaxHealth;
		}
		else
		{
			CurrentHealth += healthIncrease;
		}
	}
}

void UBaseStatsComponent::DecreaseCurrentHealth(float healthDecrease)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerDecreaseCurrentHealth(healthDecrease);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{

		if (CurrentHealth == 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Dead"));
		}
		else
		{
			CurrentHealth -= healthDecrease;
		}
	}
}

void UBaseStatsComponent::IncreaseMaxHealth(float healthIncrease)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerIncreaseMaxHealth(healthIncrease);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		MaxHealth += healthIncrease;
	}
}

void UBaseStatsComponent::IncreaseHealthRegenRate(float healthRegenIncrease)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerIncreaseHealthRegen(healthRegenIncrease);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		HealthRegenRate += healthRegenIncrease;
	}
}


void UBaseStatsComponent::DecreaseMaxHealth(float healthDecrease)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerDecreaseMaxHealth(healthDecrease);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		MaxHealth -= healthDecrease;
	}
}

void UBaseStatsComponent::DecreaseHealthRegenRate(float healthRegenDecrease)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerDecreaseHealthRegen(healthRegenDecrease);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		HealthRegenRate -= healthRegenDecrease;
	}
}

void UBaseStatsComponent::IncreaseCurrentStamina(float staminaIncrease)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerIncreaseCurrentStamina(staminaIncrease);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
			if (CurrentStamina >= MaxStamina)
			{
				CurrentStamina = MaxStamina;
			}
			else
			{
				CurrentStamina += staminaIncrease;
				UE_LOG(LogTemp, Warning, TEXT("Current Stamina: %f"), CurrentStamina);
			}
	}
}

void UBaseStatsComponent::DecreaseCurrentStamina(float staminaDecrease)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerDecreaseCurrentStamina(staminaDecrease);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		if (CurrentStamina - staminaDecrease <= 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("You are Exhaushed"))
			BaseCharacter->StopSprinting();
			CurrentStamina = 0.0f;
		}
		else
		{
			CurrentStamina -= staminaDecrease;
			UE_LOG(LogTemp, Warning, TEXT("Current Stamina: %f"), CurrentStamina)
		}
	}
}

void UBaseStatsComponent::IncreaseMaxStamina(float staminaIncrease)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerIncreaseMaxStamina(staminaIncrease);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		MaxStamina += staminaIncrease;
	}
}

void UBaseStatsComponent::IncreaseStaminaRegenRate(float staminaRegenIncrease)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerIncreaseStaminaRegen(staminaRegenIncrease);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		StaminaRegenRate += staminaRegenIncrease;
	}
}

void UBaseStatsComponent::DecreaseMaxStamina(float staminaDecrease)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerDecreaseMaxStamina(staminaDecrease);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		MaxStamina -= staminaDecrease;
	}
}

void UBaseStatsComponent::DecreaseStaminaRegenRate(float staminaRegenDecrease)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerDecreaseStaminaRegen(staminaRegenDecrease);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		StaminaRegenRate -= staminaRegenDecrease;
	}
}

void UBaseStatsComponent::ControlSprintingTimer(bool IsSprinting)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerControlSprintingTimer(IsSprinting);
		return;
	}
	else if(GetOwnerRole() == ROLE_Authority)
	{
		if (IsSprinting)
		{
			GetWorld()->GetTimerManager().PauseTimer(StaminaTimerHandle);
		}
		else
		{
			GetWorld()->GetTimerManager().UnPauseTimer(StaminaTimerHandle);
		}
	}
}


void UBaseStatsComponent::IncreaseCurrentMana(float manaIncrease)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerIncreaseCurrentMana(manaIncrease);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		if (CurrentMana >= MaxMana)
		{
			CurrentMana = MaxMana;
		}
		else
		{
			CurrentMana += manaIncrease;
		}
	}
}

void UBaseStatsComponent::DecreaseCurrentMana(float manaDecrease)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerDecreaseCurrentMana(manaDecrease);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		if (CurrentMana == 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("No Mana"));
		}
		else
		{
			CurrentMana -= manaDecrease;
		}
	}
}

void UBaseStatsComponent::IncreaseMaxMana(float manaIncrease)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerIncreaseMaxMana(manaIncrease);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		MaxMana += manaIncrease;
	}
}

void UBaseStatsComponent::IncreaseManaRegenRate(float manaRegenIncrease)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerIncreaseManaRegen(manaRegenIncrease);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		ManaRegenRate += manaRegenIncrease;
	}
}

void UBaseStatsComponent::DecreaseMaxMana(float manaDecrease)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerDecreaseMaxMana(manaDecrease);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		MaxMana -= manaDecrease;
	}
}

void UBaseStatsComponent::DecreaseManaRegenRate(float manaRegenDecrease)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerDecreaseManaRegen(manaRegenDecrease);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		ManaRegenRate -= manaRegenDecrease;
	}
}

void UBaseStatsComponent::IncreaseStrength(float increaseStrength)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerIncreaseStrength(increaseStrength);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		Strength += increaseStrength;
	}
}

void UBaseStatsComponent::IncreaseCharm(float increaseCharm)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerIncreaseCharm(increaseCharm);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		Charm += increaseCharm;
	}
}

void UBaseStatsComponent::IncreasePerception(float increasePerception)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerIncreasePerception(increasePerception);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		Perception += increasePerception;
	}
}

void UBaseStatsComponent::IncreaseBravery(float increaseBravery)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerIncreaseBravery(increaseBravery);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		Bravery += increaseBravery;
	}
}

void UBaseStatsComponent::IncreaseEndurance(float increaseEndurance)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerIncreaseEndurance(increaseEndurance);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		Endurance += increaseEndurance;
	}
}

void UBaseStatsComponent::IncreaseAgility(float increaseAgility)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerIncreaseAgility(increaseAgility);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		Agility += increaseAgility;
	}
}

void UBaseStatsComponent::IncreaseStealth(float increaseStealth)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerIncreaseStealth(increaseStealth);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		Stealth += increaseStealth;
	}
}

void UBaseStatsComponent::IncreaseIntelligence(float increaseIntelligence)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerIncreaseIntelligence(increaseIntelligence);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		Intelligence += increaseIntelligence;
	}
}

void UBaseStatsComponent::IncreaseLuck(float increaseLuck)
{
	if(GetOwnerRole() < ROLE_Authority)
	{
		ServerIncreaseLuck(increaseLuck);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		Luck += increaseLuck;
	}
}

void UBaseStatsComponent::IncreaseUnarmedCombat(float increaseUnarmedCombat)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerIncreaseUnarmedCombat(increaseUnarmedCombat);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		UnarmedCombat += increaseUnarmedCombat;
	}
}

void UBaseStatsComponent::DecreaseStrength(float decreaseStrength)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerIncreaseStrength(decreaseStrength);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		Strength -= decreaseStrength;
	}
}

void UBaseStatsComponent::DecreaseCharm(float decreaseCharm)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerIncreaseCharm(decreaseCharm);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		Charm -= decreaseCharm;
	}
}

void UBaseStatsComponent::DecreasePerception(float decreasePerception)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerIncreasePerception(decreasePerception);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		Perception -= decreasePerception;
	}
}

void UBaseStatsComponent::DecreaseBravery(float decreaseBravery)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerIncreaseBravery(decreaseBravery);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		Bravery -= decreaseBravery;
	}
}

void UBaseStatsComponent::DecreaseEndurance(float decreaseEndurance)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerIncreaseEndurance(decreaseEndurance);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		Endurance -= decreaseEndurance;
	}
}

void UBaseStatsComponent::DecreaseAgility(float decreaseAgility)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerIncreaseAgility(decreaseAgility);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		Agility -= decreaseAgility;
	}
}

void UBaseStatsComponent::DecreaseStealth(float decreaseStealth)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerDecreaseStealth(decreaseStealth);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		Stealth -= decreaseStealth;
	}
}

void UBaseStatsComponent::DecreaseIntelligence(float decreaseIntelligence)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerDecreaseIntelligence(decreaseIntelligence);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		Intelligence -= decreaseIntelligence;
	}
}

void UBaseStatsComponent::DecreaseLuck(float decreaseLuck)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerDecreaseLuck(decreaseLuck);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		Luck -= decreaseLuck;
	}
}

void UBaseStatsComponent::DecreaseUnarmedCombat(float decreaseUnarmedCombat)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerDecreaseUnarmedCombat(decreaseUnarmedCombat);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		UnarmedCombat -= decreaseUnarmedCombat;
	}
}

void UBaseStatsComponent::IncreaseCollisonRadius(float IncreaseCollisonRadius)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerIncreaseCollisonRadius(IncreaseCollisonRadius);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		CollisonRadius += IncreaseCollisonRadius;
	}
}

void UBaseStatsComponent::DecreaseCollisonRadius(float decreaseCollisonRadius)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerDecreaseCollisonRadius(decreaseCollisonRadius);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		CollisonRadius -= decreaseCollisonRadius;
	}
}

void UBaseStatsComponent::IncreaseBronzeCoins(float increaseBronzeCoin)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerIncreaseBronzeCoins(increaseBronzeCoin);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		BronzeCoin += increaseBronzeCoin;
		if (GetBronzeCoins() > 100)
		{
			BronzeCoin -= 100;
			SilverCoin += 1;
		}
	}
}

void UBaseStatsComponent::IncreaseSilverCoins(float increaseSilverCoin)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerIncreaseSilverCoins(increaseSilverCoin);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		SilverCoin += increaseSilverCoin;
		if (GetSilverCoins() > 100)
		{
			SilverCoin -= 100;
			GoldCoin += 1;
		}
	}
}

void UBaseStatsComponent::IncreaseGoldCoins(float increaseGoldCoin)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerIncreaseGoldCoins(increaseGoldCoin);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		GoldCoin += increaseGoldCoin;
	}
}

void UBaseStatsComponent::DecreaseBronzeCoins(float decreaseBronzeCoin)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerDecreaseBronzeCoins(decreaseBronzeCoin);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		if(BronzeCoin -= decreaseBronzeCoin < 0 && GetSilverCoins() > 1)
		{
			SilverCoin -= 1;
			BronzeCoin += 100;
			BronzeCoin -= decreaseBronzeCoin;
		}
		else if (BronzeCoin -= decreaseBronzeCoin < 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Not Enought Money"))
			return;
		}
		BronzeCoin -= decreaseBronzeCoin;
	}
}

void UBaseStatsComponent::DecreaseSilverCoins(float decreaseSilverCoin)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerDecreaseSilverCoins(decreaseSilverCoin);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{

		if (SilverCoin -= decreaseSilverCoin < 0 && GetGoldCoins() > 1)
		{
			GoldCoin -= 1;
			SilverCoin += 100;
			SilverCoin -= decreaseSilverCoin;
		}
		else if (SilverCoin -= decreaseSilverCoin < 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Not Enought Money"))
			return;
		}
		SilverCoin -= decreaseSilverCoin;
	}
}

void UBaseStatsComponent::DecreaseGoldCoins(float decreaseGoldCoin)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerDecreaseGoldCoins(decreaseGoldCoin);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		if (GoldCoin -= decreaseGoldCoin < 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Not Enought Money"))
			return;
		}
		GoldCoin -= decreaseGoldCoin;
	}
}

bool UBaseStatsComponent::ServerIncreaseCurrentHealth_Validate(float serverHealthIncrease)
{
	return true;
}

bool UBaseStatsComponent::ServerIncreaseMaxHealth_Validate(float serverHealthIncrease)
{
	return true;
}

bool UBaseStatsComponent::ServerDecreaseCurrentHealth_Validate(float serverHealthDecrease)
{
	return true;
}

bool UBaseStatsComponent::ServerDecreaseMaxHealth_Validate(float serverHealthDecrease)
{
	return true;
}

bool UBaseStatsComponent::ServerIncreaseCurrentStamina_Validate(float serverStaminaIncrease)
{
	return true;
}

bool UBaseStatsComponent::ServerIncreaseMaxStamina_Validate(float serverStaminaIncrease)
{
	return true;
}

bool UBaseStatsComponent::ServerDecreaseCurrentStamina_Validate(float serverStaminaDecrease)
{
	return true;
}

bool UBaseStatsComponent::ServerDecreaseMaxStamina_Validate(float serverStaminaDecrease)
{
	return true;
}

bool UBaseStatsComponent::ServerIncreaseCurrentMana_Validate(float serverManaIncrease)
{
	return true;
}

bool UBaseStatsComponent::ServerIncreaseMaxMana_Validate(float serverManaIncrease)
{
	return true;
}

bool UBaseStatsComponent::ServerDecreaseCurrentMana_Validate(float serverManaDecrease)
{
	return true;
}

bool UBaseStatsComponent::ServerDecreaseMaxMana_Validate(float serverManaDecrease)
{
	return true;
}

bool UBaseStatsComponent::ServerIncreaseStaminaRegen_Validate(float serverStaminaRegenIncrease)
{
	return true;
}

bool UBaseStatsComponent::ServerDecreaseStaminaRegen_Validate(float serverStaminaRegenDecrease)
{
	return true;
}

bool UBaseStatsComponent::ServerIncreaseManaRegen_Validate(float serverManaRegenIncrease)
{
	return true;
}

bool UBaseStatsComponent::ServerDecreaseManaRegen_Validate(float serverManaRegenDecrease)
{
	return true;
}

bool UBaseStatsComponent::ServerIncreaseHealthRegen_Validate(float serverHealthRegenIncrease)
{
	return true;
}

bool UBaseStatsComponent::ServerDecreaseHealthRegen_Validate(float serverHealthRegenDecrease)
{
	return true;
}

bool UBaseStatsComponent::ServerControlSprintingTimer_Validate(bool IsSprinting)
{
	return true;
}

bool UBaseStatsComponent::ServerIncreaseStrength_Validate(float serverStrengthIncrease)
{
	return true;
}

bool UBaseStatsComponent::ServerIncreaseCharm_Validate(float serverCharmIncrease)
{
	return true;
}

bool UBaseStatsComponent::ServerIncreasePerception_Validate(float serverPerceptionIncrease)
{
	return true;
}

bool UBaseStatsComponent::ServerIncreaseBravery_Validate(float serverBraveryIncrease)
{
	return true;
}

bool UBaseStatsComponent::ServerIncreaseEndurance_Validate(float serverEnduranceIncrease)
{
	return true;
}

bool UBaseStatsComponent::ServerIncreaseAgility_Validate(float serverAgilityIncrease)
{
	return true;
}

bool UBaseStatsComponent::ServerDecreaseStrength_Validate(float serverStrengtDecrease)
{
	return true;
}

bool UBaseStatsComponent::ServerDecreaseCharm_Validate(float serverCharmDecrease)
{
	return true;
}

bool UBaseStatsComponent::ServerDecreasePerception_Validate(float serverPerceptionDecrease)
{
	return true;
}

bool UBaseStatsComponent::ServerDecreaseEndurance_Validate(float serverEnduranceDecrease)
{
	return true;
}

bool UBaseStatsComponent::ServerDecreaseBravery_Validate(float serverBraveryDecrease)
{
	return true;
}

bool UBaseStatsComponent::ServerDecreaseAgility_Validate(float serverAgilityDecrease)
{
	return true;
}

bool UBaseStatsComponent::ServerIncreaseCollisonRadius_Validate(float serverIncreaseCollisonRadius)
{
	return true;
}

bool UBaseStatsComponent::ServerDecreaseCollisonRadius_Validate(float serverDecreaseCollisonRadius)
{
	return true;
}

bool UBaseStatsComponent::ServerIncreaseBronzeCoins_Validate(float serverBronzeCoinIncrease)
{
	return true;
}

bool UBaseStatsComponent::ServerDecreaseBronzeCoins_Validate(float serverBronzeCoinDecrease)
{
	return true;
}

bool UBaseStatsComponent::ServerIncreaseSilverCoins_Validate(float serverSilverCoinIncrease)
{
	return true;
}

bool UBaseStatsComponent::ServerDecreaseSilverCoins_Validate(float serverSilverCoinDecrease)
{
	return true;
}

bool UBaseStatsComponent::ServerIncreaseGoldCoins_Validate(float serverGoldCoinIncrease)
{
	return true;
}

bool UBaseStatsComponent::ServerDecreaseGoldCoins_Validate(float serverGoldCoinDecrease)
{
	return true;
}

bool UBaseStatsComponent::ServerIncreaseStealth_Validate(float serverStealthIncrease)
{
	return true;
}

bool UBaseStatsComponent::ServerDecreaseStealth_Validate(float serverStealthDecrease)
{
	return true;
}

bool UBaseStatsComponent::ServerIncreaseIntelligence_Validate(float serverIntelligenceIncrease)
{
	return true;
}

bool UBaseStatsComponent::ServerDecreaseIntelligence_Validate(float serverIntelligenceDecrease)
{
	return true;
}

bool UBaseStatsComponent::ServerIncreaseUnarmedCombat_Validate(float serverUnarmedCombatIncrease)
{
	return true;
}

bool UBaseStatsComponent::ServerDecreaseUnarmedCombat_Validate(float serverUnarmedCombatDecrease)
{
	return true;
}

bool UBaseStatsComponent::ServerIncreaseLuck_Validate(float serverLuckIncrease)
{
	return true;
}

bool UBaseStatsComponent::ServerDecreaseLuck_Validate(float serverLuckDecrease)
{
	return true;
}

void UBaseStatsComponent::ServerIncreaseCurrentHealth_Implementation(float serverHealthIncrease)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		IncreaseCurrentHealth(serverHealthIncrease);
	}
}

void UBaseStatsComponent::ServerDecreaseCurrentHealth_Implementation(float serverHealthDecrease)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		DecreaseCurrentHealth(serverHealthDecrease);
	}
}

void UBaseStatsComponent::ServerIncreaseMaxHealth_Implementation(float serverHealthIncrease)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		IncreaseMaxHealth(serverHealthIncrease);
	}
}

void UBaseStatsComponent::ServerDecreaseMaxHealth_Implementation(float serverHealthDecrease)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		DecreaseMaxHealth(serverHealthDecrease);
	}
}

void UBaseStatsComponent::ServerIncreaseHealthRegen_Implementation(float serverHealthRegenIncrease)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		IncreaseHealthRegenRate(serverHealthRegenIncrease);
	}
}

void UBaseStatsComponent::ServerDecreaseHealthRegen_Implementation(float serverHealthDecrease)
{
	if(GetOwnerRole() == ROLE_Authority)
	{
		DecreaseHealthRegenRate(serverHealthDecrease);
	}
}

void UBaseStatsComponent::ServerIncreaseCurrentStamina_Implementation(float serverStaminaIncrease)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		IncreaseCurrentStamina(serverStaminaIncrease);
	}
}

void UBaseStatsComponent::ServerDecreaseCurrentStamina_Implementation(float serverStaminaDecrease)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		DecreaseCurrentStamina(serverStaminaDecrease);
	}
}

void UBaseStatsComponent::ServerIncreaseMaxStamina_Implementation(float serverStaminaIncrease)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		IncreaseMaxStamina(serverStaminaIncrease);
	}
}

void UBaseStatsComponent::ServerDecreaseMaxStamina_Implementation(float serverStaminaDecrease)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		DecreaseMaxStamina(serverStaminaDecrease);
	}
}

void UBaseStatsComponent::ServerDecreaseStaminaRegen_Implementation(float serverStaminaRegenDecrease)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		DecreaseStaminaRegenRate(serverStaminaRegenDecrease);
	}
}

void UBaseStatsComponent::ServerIncreaseStaminaRegen_Implementation(float serverStaminaRegenIncrease)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		IncreaseStaminaRegenRate(serverStaminaRegenIncrease);
	}
}

void UBaseStatsComponent::ServerIncreaseCurrentMana_Implementation(float serverManaIncrease)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		IncreaseCurrentMana(serverManaIncrease);
	}
}

void UBaseStatsComponent::ServerDecreaseCurrentMana_Implementation(float serverManaDecrease)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		DecreaseCurrentMana(serverManaDecrease);
	}
}

void UBaseStatsComponent::ServerIncreaseMaxMana_Implementation(float serverManaIncrease)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		IncreaseMaxMana(serverManaIncrease);
	}
}

void UBaseStatsComponent::ServerDecreaseMaxMana_Implementation(float serverManaDecrease)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		DecreaseMaxMana(serverManaDecrease);
	}
}

void UBaseStatsComponent::ServerIncreaseManaRegen_Implementation(float serverManaRegenIncrease)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		IncreaseManaRegenRate(serverManaRegenIncrease);
	}
}

void UBaseStatsComponent::ServerDecreaseManaRegen_Implementation(float serverManaRegenDecrease)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		DecreaseManaRegenRate(serverManaRegenDecrease);
	}
}

void UBaseStatsComponent::ServerControlSprintingTimer_Implementation(bool IsSprinting)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		ControlSprintingTimer(IsSprinting);
	}
}

void UBaseStatsComponent::ServerIncreaseBronzeCoins_Implementation(float serverBronzeCoinIncrease)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		IncreaseBronzeCoins(serverBronzeCoinIncrease);
	}
}

void UBaseStatsComponent::ServerDecreaseBronzeCoins_Implementation(float serverBronzeCoinDecrease)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		DecreaseBronzeCoins(serverBronzeCoinDecrease);
	}
}

void UBaseStatsComponent::ServerIncreaseSilverCoins_Implementation(float serverSilverCoinIncrease)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		IncreaseSilverCoins(serverSilverCoinIncrease);
	}
}

void UBaseStatsComponent::ServerDecreaseSilverCoins_Implementation(float serverSilverCoinDecrease)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		DecreaseSilverCoins(serverSilverCoinDecrease);
	}
}

void UBaseStatsComponent::ServerIncreaseGoldCoins_Implementation(float serverGoldCoinIncrease)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		IncreaseGoldCoins(serverGoldCoinIncrease);
	}
}

void UBaseStatsComponent::ServerDecreaseGoldCoins_Implementation(float serverGoldCoinDecrease)
{
	if (GetOwnerRole() == ROLE_Authority) 
	{
		DecreaseGoldCoins(serverGoldCoinDecrease);
	}
}

void UBaseStatsComponent::ServerIncreaseStrength_Implementation(float serverStrengthIncrease)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		IncreaseStrength(serverStrengthIncrease);
	}
}

void UBaseStatsComponent::ServerIncreaseCharm_Implementation(float serverCharmIncrease)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		IncreaseCharm(serverCharmIncrease);
	}
}

void UBaseStatsComponent::ServerIncreasePerception_Implementation(float serverPerceptionIncrease)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		IncreasePerception(serverPerceptionIncrease);
	}
}

void UBaseStatsComponent::ServerIncreaseBravery_Implementation(float serverBraveryIncrease)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		IncreaseBravery(serverBraveryIncrease);
	}
}

void UBaseStatsComponent::ServerIncreaseEndurance_Implementation(float serverEnduranceIncrease)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		IncreaseEndurance(serverEnduranceIncrease);
	}
}

void UBaseStatsComponent::ServerIncreaseIntelligence_Implementation(float serverIntelligenceIncrease)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		IncreaseIntelligence(serverIntelligenceIncrease);
	}
}

void UBaseStatsComponent::ServerIncreaseUnarmedCombat_Implementation(float serverUnarmedCombatIncrease)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		IncreaseUnarmedCombat(serverUnarmedCombatIncrease);
	}
}

void UBaseStatsComponent::ServerIncreaseAgility_Implementation(float serverAgilityIncrease)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		IncreaseAgility(serverAgilityIncrease);
	}
}

void UBaseStatsComponent::ServerIncreaseLuck_Implementation(float serverLuckIncrease)
{
	if(GetOwnerRole() == ROLE_Authority)
	{
		IncreaseLuck(serverLuckIncrease);
	}
}

void UBaseStatsComponent::ServerIncreaseStealth_Implementation(float serverStealthIncrease)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		IncreaseStealth(serverStealthIncrease);
	}
}

void UBaseStatsComponent::ServerDecreaseStrength_Implementation(float serverStrengthDecrease)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		DecreaseStrength(serverStrengthDecrease);
	}
}

void UBaseStatsComponent::ServerDecreaseCharm_Implementation(float serverCharmDecrease)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		DecreaseCharm(serverCharmDecrease);
	}
}

void UBaseStatsComponent::ServerDecreasePerception_Implementation(float serverPerceptionDecrease)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		DecreasePerception(serverPerceptionDecrease);
	}
}

void UBaseStatsComponent::ServerDecreaseBravery_Implementation(float serverBraveryDecrease)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		DecreaseBravery(serverBraveryDecrease);
	}
}

void UBaseStatsComponent::ServerDecreaseEndurance_Implementation(float serverEnduranceDecrease)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		DecreaseEndurance(serverEnduranceDecrease);
	}
}

void UBaseStatsComponent::ServerDecreaseAgility_Implementation(float serverAgilityDecrease)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		DecreaseAgility(serverAgilityDecrease);
	}
}

void UBaseStatsComponent::ServerDecreaseStealth_Implementation(float serverStealthDecrease)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		DecreaseStealth(serverStealthDecrease);
	}
}

void UBaseStatsComponent::ServerDecreaseIntelligence_Implementation(float serverIntelligenceDecrease)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		DecreaseIntelligence(serverIntelligenceDecrease);
	}
}

void UBaseStatsComponent::ServerDecreaseLuck_Implementation(float serverLuckDecrease)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		DecreaseLuck(serverLuckDecrease);
	}
}

void UBaseStatsComponent::ServerDecreaseUnarmedCombat_Implementation(float serverUnarmedCombatDecrease)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		DecreaseUnarmedCombat(serverUnarmedCombatDecrease);
	}
}

void UBaseStatsComponent::ServerIncreaseCollisonRadius_Implementation(float serverIncreaseCollisonRadius)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		IncreaseCollisonRadius(serverIncreaseCollisonRadius);
	}
}

void UBaseStatsComponent::ServerDecreaseCollisonRadius_Implementation(float serverDecreaseCollisonRadius)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		DecreaseCollisonRadius(serverDecreaseCollisonRadius);
	}
}

float UBaseStatsComponent::GetCurrentHealth()
{
	return CurrentHealth;
}

float UBaseStatsComponent::GetMaxHealth()
{
	return MaxHealth;
}

float UBaseStatsComponent::GetHealthRegenRate()
{
	return HealthRegenRate;
}

float UBaseStatsComponent::GetCurrentStamina()
{
	return CurrentStamina;
}

float UBaseStatsComponent::GetMaxStamina()
{
	return MaxStamina;
}

float UBaseStatsComponent::GetStaminaRegenRate()
{
	return StaminaRegenRate;
}

float UBaseStatsComponent::GetCurrentMana()
{
	return CurrentMana;
}

float UBaseStatsComponent::GetMaxMana()
{
	return MaxMana;
}

float UBaseStatsComponent::GetManaRegenRate()
{
	return ManaRegenRate;
}

float UBaseStatsComponent::GetStrength()
{
	return Strength;
}

float UBaseStatsComponent::GetCharm()
{
	return Charm;
}

float UBaseStatsComponent::GetPerception()
{
	return Perception;
}

float UBaseStatsComponent::GetBravery()
{
	return Bravery;
}

float UBaseStatsComponent::GetEndurance()
{
	return Endurance;
}

float UBaseStatsComponent::GetAgility()
{
	return Agility;
}

float UBaseStatsComponent::GetStealth()
{
	return Stealth;
}

float UBaseStatsComponent::GetIntelligence()
{
	return Intelligence;
}

float UBaseStatsComponent::GetLuck()
{
	return Luck;
}

float UBaseStatsComponent::GetUnarmedCombat()
{
	return UnarmedCombat;
}

float UBaseStatsComponent::GetBronzeCoins()
{
	return BronzeCoin;
}

float UBaseStatsComponent::GetSilverCoins()
{
	return SilverCoin;
}

float UBaseStatsComponent::GetGoldCoins()
{
	return GoldCoin;
}

float UBaseStatsComponent::GetCollisonRadius()
{
	return CollisonRadius;
}
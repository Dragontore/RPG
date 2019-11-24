// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseStatsComponent.h"

#include "Net/UnrealNetwork.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "TimerManager.h"



// Sets default values for this component's properties
UBaseStatsComponent::UBaseStatsComponent()
{
	//Health defaults
	CurrentHealth = 50.f;
	MaxHealth = 100.f;
	HealthIncreaseRate = 5.f;

	//Stamina Defaults
	CurrentStamina = 50.f;
	MaxStamina = 100.f;
	StaminaIncreaseRate = 5.f;

	// Mana Defaults
	CurrentMana = 50.f;
	MaxMana = 100.f;
	ManaIncreaseRate = 5.f;

	RegenRate = 3.f;
}


// Called when the game starts
void UBaseStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	SetIsReplicated(true);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UBaseStatsComponent::HandleBaseStats, RegenRate, true);
	
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
}

void UBaseStatsComponent::HandleBaseStats()
{
	IncreaseCurrentHealth(HealthIncreaseRate);
	IncreaseCurrentStamina(StaminaIncreaseRate);
	IncreaseCurrentMana(ManaIncreaseRate);
}

void UBaseStatsComponent::IncreaseCurrentHealth(float healthIncrease)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerIncreaseCurrentHealth(healthIncrease);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		CurrentHealth += healthIncrease;

		if (CurrentHealth > MaxHealth)
		{
			CurrentHealth = MaxHealth;
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
		CurrentHealth -= healthDecrease;

		if (CurrentHealth == 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Dead"));
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
		if (MaxHealth >= MaxHealth)
		{
			MaxHealth = MaxHealth;
		}
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

void UBaseStatsComponent::IncreaseCurrentStamina(float staminaIncrease)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerIncreaseCurrentStamina(staminaIncrease);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{

		CurrentStamina += staminaIncrease;
		if (CurrentStamina >= MaxStamina)
		{
			CurrentStamina = MaxStamina;
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

		CurrentStamina -= staminaDecrease;
		if (CurrentStamina == 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Exhausted"));
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
			if (MaxStamina >= MaxStamina)
			{
				MaxStamina = MaxStamina;
			}
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

void UBaseStatsComponent::IncreaseCurrentMana(float manaIncrease)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerIncreaseCurrentMana(manaIncrease);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		CurrentMana += manaIncrease;
		if (CurrentMana >= MaxMana)
		{
			CurrentMana = MaxMana;
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
		CurrentMana -= manaDecrease;
		if (CurrentMana == 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("No Mana"));
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
		if (MaxMana >= MaxMana)
		{
			MaxMana = MaxMana;
		}
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

float UBaseStatsComponent::GetCurrentHealth()
{
	return CurrentHealth;
}

float UBaseStatsComponent::GetMaxHealth()
{
	return MaxHealth;
}

float UBaseStatsComponent::GetCurrentStamina()
{
	return CurrentStamina;
}

float UBaseStatsComponent::GetMaxStamina()
{
	return MaxStamina;
}

float UBaseStatsComponent::GetCurrentMana()
{
	return CurrentMana;
}

float UBaseStatsComponent::GetMaxMana()
{
	return MaxMana;
}
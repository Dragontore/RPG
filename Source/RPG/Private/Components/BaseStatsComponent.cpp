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
	HealthRegenRate = 5.f;

	//Stamina Defaults
	CurrentStamina = 50.f;
	MaxStamina = 100.f;
	StaminaRegenRate = 5.f;

	// Mana Defaults
	CurrentMana = 50.f;
	MaxMana = 100.f;
	ManaRegenRate = 5.f;

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
	HealthRegen(HealthRegenRate);
	StaminaRegen(StaminaRegenRate);
	ManaRegen(ManaRegenRate);
}

void UBaseStatsComponent::HealthRegen(float healthRegen)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerHealthRegen(healthRegen);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		if (CurrentHealth < MaxHealth)
		{
			CurrentHealth += healthRegen;
		}
	}
}

void UBaseStatsComponent::StaminaRegen(float staminaRegen)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerStaminaRegen(staminaRegen);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		if (CurrentStamina < MaxStamina)
		{
			CurrentStamina += staminaRegen;
		}
	}
}

void UBaseStatsComponent::ManaRegen(float ManaRegen)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerManaRegen(ManaRegen);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		if (CurrentMana < MaxMana)
		{
			CurrentMana += ManaRegen;
		}
	}
}

bool UBaseStatsComponent::ServerHealthRegen_Validate(float serverHealthRegen)
{
	return true;
}

bool UBaseStatsComponent::ServerStaminaRegen_Validate(float serverStaminaRegen)
{
	return true;
}

bool UBaseStatsComponent::ServerManaRegen_Validate(float serverManaRegen)
{
	return true;
}

void UBaseStatsComponent::ServerHealthRegen_Implementation(float serverHealthRegen)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		HealthRegen(serverHealthRegen);
	}
}

void UBaseStatsComponent::ServerStaminaRegen_Implementation(float serverStaminaRegen)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		StaminaRegen(serverStaminaRegen);
	}
}

void UBaseStatsComponent::ServerManaRegen_Implementation(float serverManaRegen)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		ManaRegen(serverManaRegen);
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
// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseStatsComponent.h"

#include "Net/UnrealNetwork.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "TimerManager.h"

#include "Character/BaseCharacter.h"



// Sets default values for this component's properties
UBaseStatsComponent::UBaseStatsComponent()
{
	//Health defaults
	CurrentHealth = 50.f;
	MaxHealth = 100.f;
	HealthIncreaseRate = 5.f;
	HealthDecreaseRate = 5.f;

	//Stamina Defaults
	CurrentStamina = 50.f;
	MaxStamina = 100.f;
	StaminaIncreaseRate = 5.f;
	StaminaDecreaseRate = 5.f;

	// Mana Defaults
	CurrentMana = 50.f;
	MaxMana = 100.f;
	ManaIncreaseRate = 5.f;
	ManaDecreaseRate = 5.f;

	HealthRegenRate = 1.f;
	StaminaRegenRate = 1.f;
	ManaRegenRate = 1.f;

	BaseCharacter = Cast<ABaseCharacter>(GetOwner());
}


// Called when the game starts
void UBaseStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	SetIsReplicated(true);

	SetTimers();
}

void UBaseStatsComponent::SetTimers()
{
	GetWorld()->GetTimerManager().SetTimer(HealthIncreaseTimerHandle, this, &UBaseStatsComponent::HandleIncreaseHealthStats, HealthRegenRate, true);
	GetWorld()->GetTimerManager().SetTimer(StaminaIncreaseTimerHandle, this, &UBaseStatsComponent::HandleIncreaseStaminaStats, StaminaRegenRate, true);
	GetWorld()->GetTimerManager().SetTimer(ManaIncreaseTimerHandle, this, &UBaseStatsComponent::HandleIncreaseManaStats, ManaRegenRate, true);
	GetWorld()->GetTimerManager().SetTimer(HealthDecreaseTimerHandle, this, &UBaseStatsComponent::HandleDecreaseHealthStats, StaminaRegenRate, true);
	GetWorld()->GetTimerManager().SetTimer(StaminaDecreaseTimerHandle, this, &UBaseStatsComponent::HandleDecreaseStaminaStats, StaminaRegenRate, true);
	GetWorld()->GetTimerManager().SetTimer(ManaDecreaseTimerHandle, this, &UBaseStatsComponent::HandleDecreaseManaStats, ManaRegenRate, true);
	GetWorld()->GetTimerManager().PauseTimer(HealthDecreaseTimerHandle);
	GetWorld()->GetTimerManager().PauseTimer(StaminaDecreaseTimerHandle);
	GetWorld()->GetTimerManager().PauseTimer(ManaDecreaseTimerHandle);
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
		GetWorld()->GetTimerManager().UnPauseTimer(HealthIncreaseTimerHandle);
		GetWorld()->GetTimerManager().PauseTimer(HealthDecreaseTimerHandle);
		CurrentHealth += healthIncrease;

		if (CurrentHealth >= MaxHealth)
		{
			CurrentHealth = MaxHealth;
			GetWorld()->GetTimerManager().PauseTimer(HealthIncreaseTimerHandle);
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
		GetWorld()->GetTimerManager().PauseTimer(HealthIncreaseTimerHandle);
		GetWorld()->GetTimerManager().UnPauseTimer(HealthDecreaseTimerHandle);

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
	}
}

void UBaseStatsComponent::IncreaseHealthRegenRate(float healthRegenIncrease)
{
	if (GetOwnerRole() < ROLE_Authority)
	{

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
		GetWorld()->GetTimerManager().UnPauseTimer(StaminaIncreaseTimerHandle);
		GetWorld()->GetTimerManager().PauseTimer(StaminaDecreaseTimerHandle);
		CurrentStamina += staminaIncrease;

		if (CurrentStamina >= MaxStamina)
		{
			CurrentStamina = MaxStamina;
			GetWorld()->GetTimerManager().PauseTimer(StaminaIncreaseTimerHandle);
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
		GetWorld()->GetTimerManager().PauseTimer(StaminaIncreaseTimerHandle);
		GetWorld()->GetTimerManager().UnPauseTimer(StaminaDecreaseTimerHandle);

			if (CurrentStamina <=0.f)
			{

				BaseCharacter->StopSprinting();
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

	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		StaminaRegenRate -= staminaRegenDecrease;
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
		GetWorld()->GetTimerManager().UnPauseTimer(ManaIncreaseTimerHandle);
		GetWorld()->GetTimerManager().PauseTimer(ManaDecreaseTimerHandle);
		CurrentMana += manaIncrease;

		if (CurrentMana >= MaxMana)
		{
			CurrentMana = MaxMana;
			GetWorld()->GetTimerManager().PauseTimer(ManaIncreaseTimerHandle);
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
		GetWorld()->GetTimerManager().PauseTimer(ManaIncreaseTimerHandle);
		GetWorld()->GetTimerManager().UnPauseTimer(ManaDecreaseTimerHandle);
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
	}
}

void UBaseStatsComponent::IncreaseManaRegenRate(float manaRegenIncrease)
{
	if (GetOwnerRole() < ROLE_Authority)
	{

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

	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		ManaRegenRate -= manaRegenDecrease;
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

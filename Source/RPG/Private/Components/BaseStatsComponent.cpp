// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseStatsComponent.h"

#include "Net/UnrealNetwork.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "TimerManager.h"



// Sets default values for this component's properties
UBaseStatsComponent::UBaseStatsComponent()
{
	CurrentHealth = 50.f;
	MaxHealth = 100.f;
	RegenRate = 3.f;
	HealthRegenRate = 5.f;
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
	DOREPLIFETIME(UBaseStatsComponent, CurrentHealth);
	DOREPLIFETIME(UBaseStatsComponent, MaxHealth);
}

void UBaseStatsComponent::HandleBaseStats()
{
	HealthRegen(HealthRegenRate);
}

void UBaseStatsComponent::HealthRegen(float healthRegen)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerHealthRegen(healthRegen);
	}
	else
	{
		if (CurrentHealth < MaxHealth)
		{
			CurrentHealth += healthRegen;
		}
	}
}

bool UBaseStatsComponent::ServerHealthRegen_Validate(float serverHealthRegen)
{
	return false;
}

void UBaseStatsComponent::ServerHealthRegen_Implementation(float serverHealthRegen)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		HealthRegen(serverHealthRegen);
	}
}

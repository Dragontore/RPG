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

}

void UBaseStatsComponent::HealthRegen(float healthRegen)
{

}

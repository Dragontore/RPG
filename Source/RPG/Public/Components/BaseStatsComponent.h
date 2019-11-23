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

	UPROPERTY(Replicated)
	float CurrentHealth;

	UPROPERTY(Replicated)
	float MaxHealth;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BaseStats")
	float RegenRate;

public:	
	// Sets default values for this component's properties
	UBaseStatsComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//Handles the bas Stats regen
	void HandleBaseStats();

public:	

	void HealthRegen(float healthRegen);
	
};

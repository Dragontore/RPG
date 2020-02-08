// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/BasePickup.h"
#include "BasePotion.generated.h"

UENUM(BlueprintType)
enum class EPickupType : uint8
{
	PT_None				UMETA(DisplayName = "None"),
	PT_Health			UMETA(DisplayName = "Health"),
	PT_Stamina			UMETA(DisplayName = "Stamina"),
	PT_Mana				UMETA(DisplayName = "Mana"),
	PT_Strength			UMETA(DisplayName = "Strength"),
	PT_Charm			UMETA(DisplayName = "Charm"),
	PT_Perception		UMETA(DisplayName = "Perception"),
	PT_Bravery			UMETA(DisplayName = "Bravery"),
	PT_Endurance		UMETA(DisplayName = "Endurance"),
	PT_Agility			UMETA(DisplayName = "Agility"),
	PT_Stealth			UMETA(DisplayName = "Stealth"),
	PT_Intelligence		UMETA(DisplayName = "Intelligence"),
	PT_Luck				UMETA(DisplayName = "Luck"),
	PT_UnarmedCombat	UMETA(DisplayName = "Unarmed Combat")
};

/**
 * 
 */
UCLASS()
class RPG_API ABasePotion : public ABasePickup
{
	GENERATED_BODY()

public:
			// Non Blueprint Public Varibles
public:
			// Non Blueprint Public Function

	virtual void UseItem(ABaseCharacter* Player) override;
public:
			// Blueprint Public Varibles
public:
			// Blueprint Public Function
protected:
			// Non Blueprint Protected Varibles

protected:
			// Non Blueprint Protected Function

	// Create Defaiult Settings
	ABasePotion();

	virtual void HandleStatTimer() override;
	virtual void UndoStatTimer() override;

protected:
			// Blueprint Protected Varibles
protected:
			// Blueprint Protected Function

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ENUMS")
	EPickupType PickupType;
	
};

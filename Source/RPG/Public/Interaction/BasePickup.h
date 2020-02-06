// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/BaseInteractable.h"
#include "BasePickup.generated.h"

class UTexture2D;

UENUM(BlueprintType)
enum class EPickupType1 : uint8
{
	PT_None				UMETA(DisplayName = "None"),
	PT_Health			UMETA(DisplayName = "Health"),
	PT_Stamina			UMETA(DisplayName = "Stamina"),
	PT_Mana				UMETA(DisplayName = "Mana"),
	PT_Money			UMETA(DisplayName = "Money"),
	PT_Stats			UMETA(DisplayName = "Stats")
};
UENUM(BlueprintType)
enum class ECoinType1 : uint8
{
	CT_None			UMETA(DisplayName = "None"),
	CT_Bronze		UMETA(DisplayName = "Bronze Coin"),
	CT_Silver		UMETA(DisplayName = "Silver Coin"),
	CT_Gold			UMETA(DisplayName = "Gold Coin")
};

UENUM(BlueprintType)
enum class EBaseStatType1 : uint8
{
	BT_None				UMETA(DisplayName = "None"),
	BT_Strength			UMETA(DisplayName = "Strength"),
	BT_Charm			UMETA(DisplayName = "Charm"),
	BT_Perception		UMETA(DisplayName = "Perception"),
	BT_Bravery			UMETA(DisplayName = "Bravery"),
	BT_Endurance		UMETA(DisplayName = "Endurance"),
	BT_Agility			UMETA(DisplayName = "Agility"),
	BT_Stealth			UMETA(DisplayName = "Stealth"),
	BT_Intelligence		UMETA(DisplayName = "Intelligence"),
	BT_Luck				UMETA(DisplayName = "Luck"),
	BT_UnarmedCombat	UMETA(DisplayName = "Unarmed Combat")
};

/**
 * 
 */
UCLASS()
class RPG_API ABasePickup : public ABaseInteractable
{
	GENERATED_BODY()

		// Sets default values for this actor's properties
		ABasePickup();

public:
			//Non Blueprint Public Variblies

public:
			//Non Blueprint Public Functions

	UFUNCTION()
	void UseItem(ABaseCharacter* Player);

	UFUNCTION()
	void InInventory(bool In);

public:
			// Blueprint Public Varibles


public:
			// Blueprint Public Functions

protected:
			// Non Blueprint Protected Varilbles

	FTimerHandle StatsTimerHandle;
	FTimerHandle UndoStatsTimerHandle;

	float Counter;

protected:
			// Non Blueprint Protected Functions

			// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetTimer();
	void ClearTimer();

	void HandleStatTimer();
	void UndoStatTimer();

	UFUNCTION()
	void OnRep_Pickedup();

protected:
			// Blueprint Protected Varibles

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Base Info")
	UTexture2D* Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ENUMS")
	EPickupType1 PickupType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ENUMS")
	ECoinType1 CoinType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ENUMS")
	EBaseStatType1 StatsType;

	UPROPERTY(ReplicatedUsing = OnRep_Pickedup)
	bool ObjectPickedup;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float IncreaseAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	bool bIsPermanent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float AmountTime;

protected:
			// Blueprint Protected Functions
};

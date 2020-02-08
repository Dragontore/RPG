// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/BaseInteractable.h"
#include "BasePickup.generated.h"

class UTexture2D;


UENUM(BlueprintType)
enum class ECoinType1 : uint8
{
	CT_None			UMETA(DisplayName = "None"),
	CT_Bronze		UMETA(DisplayName = "Bronze Coin"),
	CT_Silver		UMETA(DisplayName = "Silver Coin"),
	CT_Gold			UMETA(DisplayName = "Gold Coin")
};

/**
 * 
 */
UCLASS()
class RPG_API ABasePickup : public ABaseInteractable
{
	GENERATED_BODY()



public:
			//Non Blueprint Public Variblies

public:
			//Non Blueprint Public Functions

	UFUNCTION()
	virtual void UseItem(ABaseCharacter* Player);

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

	UPROPERTY(Replicated)
		float Weight;

protected:
			// Non Blueprint Protected Functions
			// Sets default values for this actor's properties
	ABasePickup();

			// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetTimer();
	void ClearTimer();

	virtual void HandleStatTimer();
	virtual void UndoStatTimer();

	UFUNCTION()
	void OnRep_Pickedup();

protected:
			// Blueprint Protected Varibles

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Base Info")
	UTexture2D* Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ENUMS")
	ECoinType1 CoinType;

	UPROPERTY(ReplicatedUsing = OnRep_Pickedup)
	bool ObjectPickedup;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float IncreaseAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	bool bIsPermanent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float AmountTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float PickupWeight;

protected:
			// Blueprint Protected Functions

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory.generated.h"

class APickup;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:	// Non Blueprint Varible

	// Sets default values for this component's properties
	UInventory();

	UPROPERTY(Replicated)
	TArray<APickup*> Items;

public:	// Blueprint Varible

public: // Non Blueprint Functions
	UFUNCTION()
	bool AddItem(APickup* Item);

	UFUNCTION()
	void DropItem(APickup* Item);

	UFUNCTION()
	void DropAllItems();

public: // Blueprint Functions

	UFUNCTION(BlueprintCallable, Category = "Getter")
	TArray<APickup*> GetInventoryItem();

	UFUNCTION(BlueprintCallable, Category = "Getter")
	int32 GetInventoryCount();

protected: //Non Blueprint Varibles

protected: // Blueprint Varibles

protected: // Non Blueprint Function

	// Called when the game starts
	virtual void BeginPlay() override;

protected: // Blueprint Function
		
};

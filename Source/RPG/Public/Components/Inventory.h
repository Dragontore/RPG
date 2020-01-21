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

public:	
	// Sets default values for this component's properties
	UInventory();

protected:

	UPROPERTY(Replicated)
	TArray<APickup*> Items;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	UFUNCTION()
	bool AddItem(APickup* Item);

	UFUNCTION()
	void DropItem(APickup* Item);

	UFUNCTION()
	void DropAllItems();
		
};

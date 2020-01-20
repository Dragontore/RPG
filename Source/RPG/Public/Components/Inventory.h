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

	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void Multi_PickedupItem(APickup* Item);
	bool Multi_PickedupItem_Validate(APickup* Item);
	void Multi_PickedupItem_Implementation(APickup* Item);

public:	

	UFUNCTION()
	bool AddItem(APickup* Item);

	UFUNCTION()
	void RemoveItem(APickup* Item);
		
};

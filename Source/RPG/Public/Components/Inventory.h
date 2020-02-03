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
	void DropAllItems();

public: // Blueprint Functions

	UFUNCTION(BlueprintCallable, Category = "Getter")
	TArray<APickup*> GetInventoryItem();

	UFUNCTION(BlueprintCallable, Category = "Getter")
	int32 GetInventoryCount();

	UFUNCTION(BlueprintCallable, Category = "Getter")
	int32 GetInventorySlotsAmout();

	UFUNCTION(BlueprintCallable, Category = "Setter")
	void IncreaseInventorySlotAmout(int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Setter")
	void DecreaseInventorySlotAmout(int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void DropItem(APickup* Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void UseItem(APickup* Item);

protected: //Non Blueprint Varibles

	UPROPERTY(Replicated)
	int32 InventorySlotsAmout;

protected: // Blueprint Varibles

protected: 

	// Called when the game starts
	virtual void BeginPlay() override;

protected: // Non Blueprint Function

	bool CheckIfClientHasItem(APickup* Item);
	bool RemoveItemFromInventory(APickup* Item);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerIncreaseInventorySlotsAmout(int32 Amount);
	bool ServerIncreaseInventorySlotsAmout_Validate(int32 Amount);
	void ServerIncreaseInventorySlotsAmout_Implementation(int32 Amount);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerDecreaseInventorySlotsAmout(int32 Amount);
	bool ServerDecreaseInventorySlotsAmout_Validate(int32 Amount);
	void ServerDecreaseInventorySlotsAmout_Implementation(int32 Amount);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerDropItem(APickup* Item);
	bool ServerDropItem_Validate(APickup* Item);
	void ServerDropItem_Implementation(APickup* Item);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerUseItem(APickup* Item);
	bool ServerUseItem_Validate(APickup* Item);
	void ServerUseItem_Implementation(APickup* Item);

protected: // Blueprint Function
		
};

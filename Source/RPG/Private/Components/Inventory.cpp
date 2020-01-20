// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"

#include "Net/UnrealNetwork.h"
#include "Components/StaticMeshComponent.h"

#include "Interaction/Pickup.h"

// Sets default values for this component's properties
UInventory::UInventory()
{
	
}


// Called when the game starts
void UInventory::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UInventory::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate to every client, no special condition required
	// Health Replicated Varibles
	DOREPLIFETIME(UInventory, Items);
}

bool UInventory::AddItem(APickup* Item)
{
	Items.Add(Item);
	Item->SetActorHiddenInGame(true);
	Multi_PickedupItem(Item);

	for (APickup* Pickup : Items)
	{
		UE_LOG(LogTemp, Warning, TEXT("Item: %s"), *Pickup->GetName());
	}
	return false;
}

bool UInventory::Multi_PickedupItem_Validate(APickup* Item)
{
	return true;
}

void UInventory::Multi_PickedupItem_Implementation(APickup* Item)
{
	Item->SetActorEnableCollision(false);
}

void UInventory::RemoveItem(APickup* Item)
{
}
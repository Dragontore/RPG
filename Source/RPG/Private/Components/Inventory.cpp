// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"

#include "Net/UnrealNetwork.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

#include "Interaction/Pickup.h"

// Sets default values for this component's properties
UInventory::UInventory()
{
	bReplicates = true;

	//Default Inventory Slot Amouth
	InventorySlotsAmout = 8;
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
	DOREPLIFETIME_CONDITION(UInventory, Items, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UInventory, InventorySlotsAmout, COND_OwnerOnly);
}

bool UInventory::AddItem(APickup* Item)
{
	Items.Add(Item);
	Item->InInventory(true);

	for (APickup* Pickup : Items)
	{
		UE_LOG(LogTemp, Warning, TEXT("Item: %s"), *Pickup->GetName());
	}
	return false;
}

void UInventory::DropItem(APickup* Item)
{
	
	ServerDropItem(Item);
}

bool UInventory::CheckIfClientHasItem(APickup* Item)
{
	for (APickup* Pickups : Items)
	{
		if (Pickups == Item)
		{
			return true;
		}
	}
	return false;
}

bool UInventory::RemoveItemFromInventory(APickup* Item)
{
	int32 Counter = 0;
	
	for (APickup* Pickups : Items)
	{
		if (Pickups == Item)
		{
			Items.RemoveAt(Counter);
			return true;
		}
		++Counter;
	}
	return false;
}

bool UInventory::ServerDropItem_Validate(APickup* Item)
{
	return CheckIfClientHasItem(Item);
}

void UInventory::ServerDropItem_Implementation(APickup* Item)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		FVector Location = GetOwner()->GetActorLocation();
		Location.X += FMath::RandRange(-50.0f, 100.0f);
		Location.Y += FMath::RandRange(-50.0f, 100.0f);
		FVector EndLocation = Location;
		EndLocation.Z -= 500.0f;

		FHitResult HitResult;
		FCollisionObjectQueryParams ObjectParams;
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(GetOwner());

		GetWorld()->LineTraceSingleByObjectType(OUT HitResult, Location, EndLocation, ObjectParams, QueryParams);

		if (HitResult.ImpactPoint != FVector::ZeroVector)
		{
			Location = HitResult.ImpactPoint +15.f;
		}

		Item->SetActorLocation(Location);
		Item->InInventory(false);

		RemoveItemFromInventory(Item);
	}
}

void UInventory::DropAllItems()
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		for (APickup* Pickups : Items)
		{
			DropItem(Pickups);
		}
		Items.Empty();
	}
}

TArray<APickup*> UInventory::GetInventoryItem()
{
	return Items;
}

int32 UInventory::GetInventoryCount()
{
	return Items.Num() -1;
}

int32 UInventory::GetInventorySlotsAmout()
{
	return InventorySlotsAmout;
}

void UInventory::IncreaseInventorySlotAmout(int32 Amount)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerIncreaseInventorySlotsAmout(Amount);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		InventorySlotsAmout += Amount;
	}
}

void UInventory::DecreaseInventorySlotAmout(int32 Amount)
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerDecreaseInventorySlotsAmout(Amount);
	}
	else if (GetOwnerRole() == ROLE_Authority)
	{
		InventorySlotsAmout -= Amount;
	}
}

bool UInventory::ServerIncreaseInventorySlotsAmout_Validate(int32 Amount)
{
	return true;
}

void UInventory::ServerIncreaseInventorySlotsAmout_Implementation(int32 Amount)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		IncreaseInventorySlotAmout(Amount);
	}

}

bool UInventory::ServerDecreaseInventorySlotsAmout_Validate(int32 Amount)
{
	return true;
}

void UInventory::ServerDecreaseInventorySlotsAmout_Implementation(int32 Amount)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		DecreaseInventorySlotAmout(Amount);
	}
}

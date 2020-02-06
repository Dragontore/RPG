// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseContainer.h"

#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Net/UnrealNetwork.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

#include "Character/BaseCharacter.h"
#include "Components/Inventory.h"

// Sets default values
ABaseContainer::ABaseContainer()
{
	TopMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Top Mesh");
	TopMeshComp->SetupAttachment(RootComponent);

	Inventory = CreateDefaultSubobject<UInventory>(TEXT("Inventory component"));

	bReplicates = true;

}

// Called when the game starts or when spawned
void ABaseContainer::BeginPlay()
{
	Super::BeginPlay();
	
}

UInventory* ABaseContainer::GetInventoryComponent()
{
	return Inventory;
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Net/UnrealNetwork.h"

#include "Character/BaseCharacter.h"
#include "Components/BaseStatsComponent.h"

// Sets default values
APickup::APickup()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = MeshComp;

	CollisonSphere = CreateDefaultSubobject<USphereComponent>("Collision Sphere");
	CollisonSphere->SetupAttachment(MeshComp);

	PickupType = EPickupType::PT_None;

	IncreaseAmount = 20.0f;
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	SetReplicates(true);
	
}

bool APickup::MultiDestroyActor_Validate()
{
	return true;
}

void APickup::MultiDestroyActor_Implementation()
{
	Destroy();
}

void APickup::UseItem(ABaseCharacter* Player)
{
	if (Role == ROLE_Authority)
	{
		if (PickupType == EPickupType::PT_Health)
		{
			Player->BaseStatsComp->IncreaseCurrentHealth(IncreaseAmount); //SetIncrease Amouth
		}
		else if (PickupType == EPickupType::PT_Stamina)
		{
			Player->BaseStatsComp->IncreaseCurrentStamina(IncreaseAmount); //SetIncrease Amouth
		}
		else if (PickupType == EPickupType::PT_Mana)
		{
			Player->BaseStatsComp->IncreaseCurrentMana(IncreaseAmount); //SetIncrease Amouth
		}
		MultiDestroyActor();
	}
}




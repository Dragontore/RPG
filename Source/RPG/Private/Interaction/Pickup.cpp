// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Net/UnrealNetwork.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

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
	CoinType = ECoinType::CT_None;
	StatsType = EBaseStatType::BT_None;

	IncreaseAmount = 20.0f;
	AmountTime = 0.0f;
	bIsPermanent = false;
	Counter = 0.f;
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	SetReplicates(true);

	
}

void APickup::SetTimer()
{
	if (Role == ROLE_Authority)
	{
		GetWorld()->GetTimerManager().SetTimer(StatsTimerHandle, this, &APickup::HandleStatTimer, 1, true);
	}
}

void APickup::ClearTimer()
{
	if (Role == ROLE_Authority)
	{
		GetWorld()->GetTimerManager().ClearTimer(StatsTimerHandle);
		GetWorld()->GetTimerManager().ClearTimer(UndoStatsTimerHandle);
	}
}

void APickup::HandleStatTimer()
{
	if (Role == ROLE_Authority)
	{
		ABaseCharacter* Player = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (StatsType == EBaseStatType::BT_Agility)
		{
			Counter++;
				Player->BaseStatsComp->IncreaseAgility(IncreaseAmount);
				UE_LOG(LogTemp, Warning, TEXT("Stat Timer Called: %f"), Counter);
				if (Counter == AmountTime)
				{
					ClearTimer();
					GetWorld()->GetTimerManager().SetTimer(UndoStatsTimerHandle, this, &APickup::UndoStatTimer, 1, true);
					UndoStatTimer();
				 
				}
		}
	}
}

void APickup::UndoStatTimer()
{
	if (Role == ROLE_Authority)
	{
		ABaseCharacter* Player = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		Counter--;
		UE_LOG(LogTemp, Warning, TEXT("Stat Timer Called: %f"), Counter);
		Player->BaseStatsComp->DecreaseAgility(IncreaseAmount);
		if (Counter == 0)
		{
			ClearTimer();
		}
	}
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
		else if (PickupType == EPickupType::PT_Money)
		{
			if (CoinType == ECoinType::CT_Bronze)
			{
				Player->BaseStatsComp->IncreaseBronzeCoins(IncreaseAmount);
			}
			else if (CoinType == ECoinType::CT_Silver)
			{
				Player->BaseStatsComp->IncreaseSilverCoins(IncreaseAmount);
			}
			else if (CoinType == ECoinType::CT_Gold)
			{
				Player->BaseStatsComp->IncreaseGoldCoins(IncreaseAmount);
			}
			
		}
		else if (PickupType == EPickupType::PT_Stats)
		{
			if (StatsType == EBaseStatType::BT_Agility)
			{

				if (bIsPermanent == true)
				{
					Player->BaseStatsComp->IncreaseAgility(IncreaseAmount);
				}
				else if (bIsPermanent == false)
				{
					SetTimer();
				}
			}
		}
		//MultiDestroyActor();
	}
}




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

	IncreaseAmount = 00.0f;
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
				if (Counter == AmountTime)
				{
					ClearTimer();
					GetWorld()->GetTimerManager().SetTimer(UndoStatsTimerHandle, this, &APickup::UndoStatTimer, 1, true);
					UndoStatTimer();
				 
				}
		}
		else if (StatsType == EBaseStatType::BT_Bravery)
		{
			Counter++;
			Player->BaseStatsComp->IncreaseBravery(IncreaseAmount);
				if (Counter == AmountTime)
				{
					ClearTimer();
					GetWorld()->GetTimerManager().SetTimer(UndoStatsTimerHandle, this, &APickup::UndoStatTimer, 1, true);
					UndoStatTimer();
				}
		}
		else if (StatsType == EBaseStatType::BT_Charm)
		{
			Counter++;
			Player->BaseStatsComp->IncreaseCharm(IncreaseAmount);
			if (Counter == AmountTime)
			{
				ClearTimer();
				GetWorld()->GetTimerManager().SetTimer(UndoStatsTimerHandle, this, &APickup::UndoStatTimer, 1, true);
				UndoStatTimer();

			}
		}
		else if (StatsType == EBaseStatType::BT_Endurance)
		{
			Counter++;
			Player->BaseStatsComp->IncreaseEndurance(IncreaseAmount);
			if (Counter == AmountTime)
			{
				ClearTimer();
				GetWorld()->GetTimerManager().SetTimer(UndoStatsTimerHandle, this, &APickup::UndoStatTimer, 1, true);
				UndoStatTimer();
			}
		}
		else if (StatsType == EBaseStatType::BT_Intelligence)
		{
			Counter++;
			Player->BaseStatsComp->IncreaseIntelligence(IncreaseAmount);
			if (Counter == AmountTime)
			{
				ClearTimer();
				GetWorld()->GetTimerManager().SetTimer(UndoStatsTimerHandle, this, &APickup::UndoStatTimer, 1, true);
				UndoStatTimer();
			}
		}
		else if (StatsType == EBaseStatType::BT_Luck)
		{
			Counter++;
			Player->BaseStatsComp->IncreaseLuck(IncreaseAmount);
			if (Counter == AmountTime)
			{
				ClearTimer();
				GetWorld()->GetTimerManager().SetTimer(UndoStatsTimerHandle, this, &APickup::UndoStatTimer, 1, true);
				UndoStatTimer();
			}
		}
		else if (StatsType == EBaseStatType::BT_Perception)
		{
			Counter++;
			Player->BaseStatsComp->IncreasePerception(IncreaseAmount);
			if (Counter == AmountTime)
			{
				ClearTimer();
				GetWorld()->GetTimerManager().SetTimer(UndoStatsTimerHandle, this, &APickup::UndoStatTimer, 1, true);
				UndoStatTimer();
			}
		}
		else if (StatsType == EBaseStatType::BT_Stealth)
		{
			Counter++;
			Player->BaseStatsComp->IncreaseStealth(IncreaseAmount);
			if (Counter == AmountTime)
			{
				ClearTimer();
				GetWorld()->GetTimerManager().SetTimer(UndoStatsTimerHandle, this, &APickup::UndoStatTimer, 1, true);
				UndoStatTimer();
			}
		}
		else if (StatsType == EBaseStatType::BT_Strength)
		{
			Counter++;
			Player->BaseStatsComp->IncreaseStrength(IncreaseAmount);
			if (Counter == AmountTime)
			{
				ClearTimer();
				GetWorld()->GetTimerManager().SetTimer(UndoStatsTimerHandle, this, &APickup::UndoStatTimer, 1, true);
				UndoStatTimer();
			}
		}
		else if (StatsType == EBaseStatType::BT_UnarmedCombat)
		{
			Counter++;
			Player->BaseStatsComp->IncreaseUnarmedCombat(IncreaseAmount);
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
		if (StatsType == EBaseStatType::BT_Agility)
		{
			Player->BaseStatsComp->DecreaseAgility(IncreaseAmount);
			if (Counter == 0)
			{
				ClearTimer();
			}
		}
		else if (StatsType == EBaseStatType::BT_Bravery)
		{
			Player->BaseStatsComp->DecreaseBravery(IncreaseAmount);
			if (Counter == 0)
			{
				ClearTimer();
			}
		}
		else if (StatsType == EBaseStatType::BT_Charm)
		{
			Player->BaseStatsComp->DecreaseCharm(IncreaseAmount);
			if (Counter == 0)
			{
				ClearTimer();
			}
		}
		else if (StatsType == EBaseStatType::BT_Endurance)
		{
			Player->BaseStatsComp->DecreaseEndurance(IncreaseAmount);
			if (Counter == 0)
			{
				ClearTimer();
			}
		}
		else if (StatsType == EBaseStatType::BT_Intelligence)
		{
			Player->BaseStatsComp->DecreaseIntelligence(IncreaseAmount);
			if (Counter == 0)
			{
				ClearTimer();
			}
		}
		else if (StatsType == EBaseStatType::BT_Luck)
		{
			Player->BaseStatsComp->DecreaseLuck(IncreaseAmount);
			if (Counter == 0)
			{
				ClearTimer();
			}
		}
		else if (StatsType == EBaseStatType::BT_Perception)
		{
			Player->BaseStatsComp->DecreasePerception(IncreaseAmount);
			if (Counter == 0)
			{
				ClearTimer();
			}
		}
		else if (StatsType == EBaseStatType::BT_Stealth)
		{
			Player->BaseStatsComp->DecreaseStealth(IncreaseAmount);
			if (Counter == 0)
			{
				ClearTimer();
			}
		}
		else if (StatsType == EBaseStatType::BT_Strength)
		{
			Player->BaseStatsComp->DecreaseStrength(IncreaseAmount);
			if (Counter == 0)
			{
				ClearTimer();
			}
		}
		else if (StatsType == EBaseStatType::BT_UnarmedCombat)
		{
			Player->BaseStatsComp->DecreaseUnarmedCombat(IncreaseAmount);
			if (Counter == 0)
			{
				ClearTimer();
			}
		}
	}
}

FString APickup::GetUseText() const
{
		return FString::Printf(TEXT("%s: Press E To %s"), *Name, *Action);
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
			if (bIsPermanent == true)
			{
				Player->BaseStatsComp->IncreaseMaxHealth(IncreaseAmount);
			}
			else if (bIsPermanent == false)
			{
				Player->BaseStatsComp->IncreaseCurrentHealth(IncreaseAmount); 
			}
		}
		else if (PickupType == EPickupType::PT_Stamina)
		{
			if (bIsPermanent == true)
			{
				Player->BaseStatsComp->IncreaseMaxStamina(IncreaseAmount);
			}
			else if (bIsPermanent == false)
			{
				Player->BaseStatsComp->IncreaseCurrentStamina(IncreaseAmount); 
			}
		}
		else if (PickupType == EPickupType::PT_Mana)
		{
			if (bIsPermanent == true)
			{
				Player->BaseStatsComp->IncreaseMaxMana(IncreaseAmount);
			}
			else if (bIsPermanent == false)
			{
				Player->BaseStatsComp->IncreaseCurrentMana(IncreaseAmount);
			}
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
			else if (StatsType == EBaseStatType::BT_Bravery)
			{
				if (bIsPermanent == true)
				{
					Player->BaseStatsComp->IncreaseBravery(IncreaseAmount);
				}
				else if (bIsPermanent == false)
				{
					SetTimer();
				}
			}
			else if (StatsType == EBaseStatType::BT_Charm)
			{
				if (bIsPermanent == true)
				{
					Player->BaseStatsComp->IncreaseCharm(IncreaseAmount);
				}
				else if (bIsPermanent == false)
				{
					SetTimer();
				}
			}
			else if (StatsType == EBaseStatType::BT_Endurance)
			{
				if (bIsPermanent == true)
				{
					Player->BaseStatsComp->IncreaseEndurance(IncreaseAmount);
				}
				else if (bIsPermanent == false)
				{
					SetTimer();
				}
			}
			else if (StatsType == EBaseStatType::BT_Intelligence)
			{
				if (bIsPermanent == true)
				{
					Player->BaseStatsComp->IncreaseIntelligence(IncreaseAmount);
				}
				else if (bIsPermanent == false)
				{
					SetTimer();
				}
			}
			else if (StatsType == EBaseStatType::BT_Luck)
			{
				if (bIsPermanent == true)
				{
					Player->BaseStatsComp->IncreaseLuck(IncreaseAmount);
				}
				else if (bIsPermanent == false)
				{
					SetTimer();
				}
			}
			else if (StatsType == EBaseStatType::BT_Perception)
			{
				if (bIsPermanent == true)
				{
					Player->BaseStatsComp->IncreasePerception(IncreaseAmount);
				}
				else if (bIsPermanent == false)
				{
					SetTimer();
				}
			}
			else if (StatsType == EBaseStatType::BT_Stealth)
			{
				if (bIsPermanent == true)
				{
					Player->BaseStatsComp->IncreaseStealth(IncreaseAmount);
				}
				else if (bIsPermanent == false)
				{
					SetTimer();
				}
			}
			else if (StatsType == EBaseStatType::BT_Strength)
			{
				if (bIsPermanent == true)
				{
					Player->BaseStatsComp->IncreaseStrength(IncreaseAmount);
				}
				else if (bIsPermanent == false)
				{
					SetTimer();
				}
			}
			else if (StatsType == EBaseStatType::BT_UnarmedCombat)
			{
			if (bIsPermanent == true)
			{
				Player->BaseStatsComp->IncreaseUnarmedCombat(IncreaseAmount);
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




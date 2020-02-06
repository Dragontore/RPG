// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePickup.h"

#include "Net/UnrealNetwork.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Texture2D.h"
#include "Components/StaticMeshComponent.h"

#include "Components/BaseStatsComponent.h"
#include "Character/BaseCharacter.h"

// Sets default values
ABasePickup::ABasePickup()
{

	Thumbnail = CreateDefaultSubobject<UTexture2D>(TEXT("Thumbnail"));

	PickupType = EPickupType1::PT_None;
	CoinType = ECoinType1::CT_None;
	StatsType = EBaseStatType1::BT_None;

	IncreaseAmount = 00.0f;
	AmountTime = 0.0f;
	bIsPermanent = false;
	Counter = 0.f;
	bReplicates = true;
	ObjectPickedup = false;
	bReplicateMovement = true;
}

// Called when the game starts or when spawned
void ABasePickup::BeginPlay()
{
	Super::BeginPlay();

}

void ABasePickup::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate to every client, no special condition required
	DOREPLIFETIME(ABasePickup, ObjectPickedup);
}

void ABasePickup::SetTimer()
{
	if (Role == ROLE_Authority)
	{
		GetWorld()->GetTimerManager().SetTimer(StatsTimerHandle, this, &ABasePickup::HandleStatTimer, 1, true);
	}
}

void ABasePickup::ClearTimer()
{
	if (Role == ROLE_Authority)
	{
		GetWorld()->GetTimerManager().ClearTimer(StatsTimerHandle);
		GetWorld()->GetTimerManager().ClearTimer(UndoStatsTimerHandle);
	}
}

void ABasePickup::HandleStatTimer()
{
	if (Role == ROLE_Authority)
	{
		ABaseCharacter* Player = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (StatsType == EBaseStatType1::BT_Agility)
		{
			Counter++;
			Player->BaseStatsComp->IncreaseAgility(IncreaseAmount);
			if (Counter == AmountTime)
			{
				ClearTimer();
				GetWorld()->GetTimerManager().SetTimer(UndoStatsTimerHandle, this, &ABasePickup::UndoStatTimer, 1, true);
				UndoStatTimer();

			}
		}
		else if (StatsType == EBaseStatType1::BT_Bravery)
		{
			Counter++;
			Player->BaseStatsComp->IncreaseBravery(IncreaseAmount);
			if (Counter == AmountTime)
			{
				ClearTimer();
				GetWorld()->GetTimerManager().SetTimer(UndoStatsTimerHandle, this, &ABasePickup::UndoStatTimer, 1, true);
				UndoStatTimer();
			}
		}
		else if (StatsType == EBaseStatType1::BT_Charm)
		{
			Counter++;
			Player->BaseStatsComp->IncreaseCharm(IncreaseAmount);
			if (Counter == AmountTime)
			{
				ClearTimer();
				GetWorld()->GetTimerManager().SetTimer(UndoStatsTimerHandle, this, &ABasePickup::UndoStatTimer, 1, true);
				UndoStatTimer();

			}
		}
		else if (StatsType == EBaseStatType1::BT_Endurance)
		{
			Counter++;
			Player->BaseStatsComp->IncreaseEndurance(IncreaseAmount);
			if (Counter == AmountTime)
			{
				ClearTimer();
				GetWorld()->GetTimerManager().SetTimer(UndoStatsTimerHandle, this, &ABasePickup::UndoStatTimer, 1, true);
				UndoStatTimer();
			}
		}
		else if (StatsType == EBaseStatType1::BT_Intelligence)
		{
			Counter++;
			Player->BaseStatsComp->IncreaseIntelligence(IncreaseAmount);
			if (Counter == AmountTime)
			{
				ClearTimer();
				GetWorld()->GetTimerManager().SetTimer(UndoStatsTimerHandle, this, &ABasePickup::UndoStatTimer, 1, true);
				UndoStatTimer();
			}
		}
		else if (StatsType == EBaseStatType1::BT_Luck)
		{
			Counter++;
			Player->BaseStatsComp->IncreaseLuck(IncreaseAmount);
			if (Counter == AmountTime)
			{
				ClearTimer();
				GetWorld()->GetTimerManager().SetTimer(UndoStatsTimerHandle, this, &ABasePickup::UndoStatTimer, 1, true);
				UndoStatTimer();
			}
		}
		else if (StatsType == EBaseStatType1::BT_Perception)
		{
			Counter++;
			Player->BaseStatsComp->IncreasePerception(IncreaseAmount);
			if (Counter == AmountTime)
			{
				ClearTimer();
				GetWorld()->GetTimerManager().SetTimer(UndoStatsTimerHandle, this, &ABasePickup::UndoStatTimer, 1, true);
				UndoStatTimer();
			}
		}
		else if (StatsType == EBaseStatType1::BT_Stealth)
		{
			Counter++;
			Player->BaseStatsComp->IncreaseStealth(IncreaseAmount);
			if (Counter == AmountTime)
			{
				ClearTimer();
				GetWorld()->GetTimerManager().SetTimer(UndoStatsTimerHandle, this, &ABasePickup::UndoStatTimer, 1, true);
				UndoStatTimer();
			}
		}
		else if (StatsType == EBaseStatType1::BT_Strength)
		{
			Counter++;
			Player->BaseStatsComp->IncreaseStrength(IncreaseAmount);
			if (Counter == AmountTime)
			{
				ClearTimer();
				GetWorld()->GetTimerManager().SetTimer(UndoStatsTimerHandle, this, &ABasePickup::UndoStatTimer, 1, true);
				UndoStatTimer();
			}
		}
		else if (StatsType == EBaseStatType1::BT_UnarmedCombat)
		{
			Counter++;
			Player->BaseStatsComp->IncreaseUnarmedCombat(IncreaseAmount);
			if (Counter == AmountTime)
			{
				ClearTimer();
				GetWorld()->GetTimerManager().SetTimer(UndoStatsTimerHandle, this, &ABasePickup::UndoStatTimer, 1, true);
				UndoStatTimer();
			}
		}
		return;
	}
}

void ABasePickup::UndoStatTimer()
{
	if (Role == ROLE_Authority)
	{
		ABaseCharacter* Player = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		Counter--;
		if (StatsType == EBaseStatType1::BT_Agility)
		{
			Player->BaseStatsComp->DecreaseAgility(IncreaseAmount);
			if (Counter == 0)
			{
				ClearTimer();
			}
		}
		else if (StatsType == EBaseStatType1::BT_Bravery)
		{
			Player->BaseStatsComp->DecreaseBravery(IncreaseAmount);
			if (Counter == 0)
			{
				ClearTimer();
			}
		}
		else if (StatsType == EBaseStatType1::BT_Charm)
		{
			Player->BaseStatsComp->DecreaseCharm(IncreaseAmount);
			if (Counter == 0)
			{
				ClearTimer();
			}
		}
		else if (StatsType == EBaseStatType1::BT_Endurance)
		{
			Player->BaseStatsComp->DecreaseEndurance(IncreaseAmount);
			if (Counter == 0)
			{
				ClearTimer();
			}
		}
		else if (StatsType == EBaseStatType1::BT_Intelligence)
		{
			Player->BaseStatsComp->DecreaseIntelligence(IncreaseAmount);
			if (Counter == 0)
			{
				ClearTimer();
			}
		}
		else if (StatsType == EBaseStatType1::BT_Luck)
		{
			Player->BaseStatsComp->DecreaseLuck(IncreaseAmount);
			if (Counter == 0)
			{
				ClearTimer();
			}
		}
		else if (StatsType == EBaseStatType1::BT_Perception)
		{
			Player->BaseStatsComp->DecreasePerception(IncreaseAmount);
			if (Counter == 0)
			{
				ClearTimer();
			}
		}
		else if (StatsType == EBaseStatType1::BT_Stealth)
		{
			Player->BaseStatsComp->DecreaseStealth(IncreaseAmount);
			if (Counter == 0)
			{
				ClearTimer();
			}
		}
		else if (StatsType == EBaseStatType1::BT_Strength)
		{
			Player->BaseStatsComp->DecreaseStrength(IncreaseAmount);
			if (Counter == 0)
			{
				ClearTimer();
			}
		}
		else if (StatsType == EBaseStatType1::BT_UnarmedCombat)
		{
			Player->BaseStatsComp->DecreaseUnarmedCombat(IncreaseAmount);
			if (Counter == 0)
			{
				ClearTimer();
			}
		}
	}
}

void ABasePickup::UseItem(ABaseCharacter* Player)
{
	if (Role == ROLE_Authority)
	{
		if (PickupType == EPickupType1::PT_Health)
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
		else if (PickupType == EPickupType1::PT_Stamina)
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
		else if (PickupType == EPickupType1::PT_Mana)
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
		else if (PickupType == EPickupType1::PT_Money)
		{
			if (CoinType == ECoinType1::CT_Bronze)
			{
				Player->BaseStatsComp->IncreaseBronzeCoins(IncreaseAmount);
			}
			else if (CoinType == ECoinType1::CT_Silver)
			{
				Player->BaseStatsComp->IncreaseSilverCoins(IncreaseAmount);
			}
			else if (CoinType == ECoinType1::CT_Gold)
			{
				Player->BaseStatsComp->IncreaseGoldCoins(IncreaseAmount);
			}

		}
		else if (PickupType == EPickupType1::PT_Stats)
		{
			if (StatsType == EBaseStatType1::BT_Agility)
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
			else if (StatsType == EBaseStatType1::BT_Bravery)
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
			else if (StatsType == EBaseStatType1::BT_Charm)
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
			else if (StatsType == EBaseStatType1::BT_Endurance)
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
			else if (StatsType == EBaseStatType1::BT_Intelligence)
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
			else if (StatsType == EBaseStatType1::BT_Luck)
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
			else if (StatsType == EBaseStatType1::BT_Perception)
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
			else if (StatsType == EBaseStatType1::BT_Stealth)
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
			else if (StatsType == EBaseStatType1::BT_Strength)
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
			else if (StatsType == EBaseStatType1::BT_UnarmedCombat)
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
		Destroy();
		return;
	}
}

void ABasePickup::OnRep_Pickedup()
{
		UStaticMeshComponent* Mesh = this->FindComponentByClass<UStaticMeshComponent>();
		if (Mesh)
		{
			UE_LOG(LogTemp, Warning, TEXT("Interact Function called"));
			Mesh->SetHiddenInGame(ObjectPickedup);
			this->SetActorEnableCollision(!ObjectPickedup);
		}
}

void ABasePickup::InInventory(bool In)
{
	if (Role == ROLE_Authority)
	{
		ObjectPickedup = In;
		OnRep_Pickedup();
	}
}
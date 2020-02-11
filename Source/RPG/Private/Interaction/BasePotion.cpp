// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePotion.h"

#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "TimerManager.h"

#include "Character/BaseCharacter.h"
#include "Components/BaseStatsComponent.h"

ABasePotion::ABasePotion()
{
	PickupType = EPickupType::PT_None;
	bReplicateMovement = true;
	bReplicates = true;
}

void ABasePotion::HandleStatTimer()
{
	if (Role == ROLE_Authority)
	{
		Super::HandleStatTimer();
		ABaseCharacter* Player = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		switch (PickupType)
		{
			case EPickupType::PT_Agility:
			{
				Counter++;
				Player->BaseStatsComp->IncreaseAgility(IncreaseAmount);
				if (Counter == AmountTime)
					{
					ClearTimer();
					GetWorld()->GetTimerManager().SetTimer(UndoStatsTimerHandle, this, &ABasePotion::UndoStatTimer, 1, true);
					UndoStatTimer();
					}
				break;
			}
			case EPickupType::PT_Bravery:
			{
				Counter++;
				Player->BaseStatsComp->IncreaseBravery(IncreaseAmount);
				if (Counter == AmountTime)
				{
					ClearTimer();
					GetWorld()->GetTimerManager().SetTimer(UndoStatsTimerHandle, this, &ABasePotion::UndoStatTimer, 1, true);
					UndoStatTimer();
				}
				break;
			}
			case EPickupType::PT_Charm:
			{
				Counter++;
				Player->BaseStatsComp->IncreaseCharm(IncreaseAmount);
				if (Counter == AmountTime)
				{
					ClearTimer();
					GetWorld()->GetTimerManager().SetTimer(UndoStatsTimerHandle, this, &ABasePotion::UndoStatTimer, 1, true);
					UndoStatTimer();
				}
				break;
			}
			case EPickupType::PT_Endurance:
			{
				Counter++;
				Player->BaseStatsComp->IncreaseEndurance(IncreaseAmount);
				if (Counter == AmountTime)
				{
					ClearTimer();
					GetWorld()->GetTimerManager().SetTimer(UndoStatsTimerHandle, this, &ABasePotion::UndoStatTimer, 1, true);
					UndoStatTimer();
				}
				break;
			}
			case EPickupType::PT_Intelligence:
			{
				Counter++;
				Player->BaseStatsComp->IncreaseIntelligence(IncreaseAmount);
				if (Counter == AmountTime)
				{
					ClearTimer();
					GetWorld()->GetTimerManager().SetTimer(UndoStatsTimerHandle, this, &ABasePotion::UndoStatTimer, 1, true);
					UndoStatTimer();
				}
				break;
			}
			case EPickupType::PT_Luck:
			{
				Counter++;
				Player->BaseStatsComp->IncreaseLuck(IncreaseAmount);
				if (Counter == AmountTime)
				{
					ClearTimer();
					GetWorld()->GetTimerManager().SetTimer(UndoStatsTimerHandle, this, &ABasePotion::UndoStatTimer, 1, true);
					UndoStatTimer();
				}
				break;
			}
			case EPickupType::PT_Perception:
			{
				Counter++;
				Player->BaseStatsComp->IncreasePerception(IncreaseAmount);
				if (Counter == AmountTime)
				{
					ClearTimer();
					GetWorld()->GetTimerManager().SetTimer(UndoStatsTimerHandle, this, &ABasePotion::UndoStatTimer, 1, true);
					UndoStatTimer();
				}
				break;
			}
			case EPickupType::PT_Stealth:
			{
				Counter++;
				Player->BaseStatsComp->IncreaseStealth(IncreaseAmount);
				if (Counter == AmountTime)
				{
					ClearTimer();
					GetWorld()->GetTimerManager().SetTimer(UndoStatsTimerHandle, this, &ABasePotion::UndoStatTimer, 1, true);
					UndoStatTimer();
				}
				break;
			}
			case EPickupType::PT_Strength:
			{
				Counter++;
				Player->BaseStatsComp->IncreaseStrength(IncreaseAmount);
				if (Counter == AmountTime)
				{
					ClearTimer();
					GetWorld()->GetTimerManager().SetTimer(UndoStatsTimerHandle, this, &ABasePotion::UndoStatTimer, 1, true);
					UndoStatTimer();
				}
				break;
			}
			case EPickupType::PT_UnarmedCombat:
			{
				Counter++;
				Player->BaseStatsComp->IncreaseUnarmedCombat(IncreaseAmount);
				if (Counter == AmountTime)
				{
					ClearTimer();
					GetWorld()->GetTimerManager().SetTimer(UndoStatsTimerHandle, this, &ABasePotion::UndoStatTimer, 1, true);
					UndoStatTimer();
				}
				break;
			}
		}
	}
}

void ABasePotion::UndoStatTimer()
{
	if (Role == ROLE_Authority)
	{
		Super::UndoStatTimer();

		ABaseCharacter* Player = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		Counter--;
		switch (PickupType)
		{
			case EPickupType::PT_Agility:
			{
				Player->BaseStatsComp->DecreaseAgility(IncreaseAmount);
				if (Counter == 0)
				{
					ClearTimer();
				}
				break;
			}
			case EPickupType::PT_Bravery:
			{
				Player->BaseStatsComp->DecreaseBravery(IncreaseAmount);
				if (Counter == 0)
				{
					ClearTimer();
				}
				break;
			}
			case EPickupType::PT_Charm:
			{
				Player->BaseStatsComp->DecreaseCharm(IncreaseAmount);
				if (Counter == 0)
				{
					ClearTimer();
				}
				break;
			}
			case EPickupType::PT_Endurance:
			{
				Player->BaseStatsComp->DecreaseEndurance(IncreaseAmount);
				if (Counter == 0)
				{
					ClearTimer();
				}
				break;
			}
			case EPickupType::PT_Intelligence:
			{
				Player->BaseStatsComp->DecreaseIntelligence(IncreaseAmount);
				if (Counter == 0)
				{
					ClearTimer();
				}
				break;
			}
			case EPickupType::PT_Luck:
			{
				Player->BaseStatsComp->DecreaseLuck(IncreaseAmount);
				if (Counter == 0)
				{
					ClearTimer();
				}
				break;
			}
			case EPickupType::PT_Perception:
			{
				Player->BaseStatsComp->DecreasePerception(IncreaseAmount);
				if (Counter == 0)
				{
					ClearTimer();
				}
				break;
			}
			case EPickupType::PT_Stealth:
			{
				Player->BaseStatsComp->DecreaseStealth(IncreaseAmount);
				if (Counter == 0)
				{
					ClearTimer();
				}
				break;
			}
			case EPickupType::PT_Strength:
			{
				Player->BaseStatsComp->DecreaseStrength(IncreaseAmount);
				if (Counter == 0)
				{
					ClearTimer();
				}
				break;
			}
			case EPickupType::PT_UnarmedCombat:
			{
				Player->BaseStatsComp->DecreaseUnarmedCombat(IncreaseAmount);
				if (Counter == 0)
				{
					ClearTimer();
				}
				break;
			}
		}
	}
}

void ABasePotion::UseItem(ABaseCharacter* Player)
{
	if (Role == ROLE_Authority)
	{

		Super::UseItem(Player);
		switch (PickupType)
		{
			case EPickupType::PT_Health:
			{
				if (bIsPermanent == true)
				{
					Player->BaseStatsComp->IncreaseMaxHealth(IncreaseAmount);
				}
				else if (bIsPermanent == false)
				{
					Player->BaseStatsComp->IncreaseCurrentHealth(IncreaseAmount);
				}
				break;
			}
			case EPickupType::PT_Stamina:
			{
				if (bIsPermanent == true)
				{
					Player->BaseStatsComp->IncreaseMaxStamina(IncreaseAmount);
				}
				else if (bIsPermanent == false)
				{
					Player->BaseStatsComp->IncreaseCurrentStamina(IncreaseAmount);
				}
				break;
			}
			case EPickupType::PT_Mana:
			{
				if (bIsPermanent == true)
				{
					Player->BaseStatsComp->IncreaseMaxMana(IncreaseAmount);
				}
				else if (bIsPermanent == false)
				{
					Player->BaseStatsComp->IncreaseCurrentMana(IncreaseAmount);
				}
				break;
			}
			case EPickupType::PT_Strength:
			{
				if (bIsPermanent == true)
				{
					Player->BaseStatsComp->IncreaseStrength(IncreaseAmount);
				}
				else if (bIsPermanent == false)
				{
					SetTimer();
				}
				break;
			}
			case EPickupType::PT_Charm:
			{
				if (bIsPermanent == true)
				{
					Player->BaseStatsComp->IncreaseCharm(IncreaseAmount);
				}
				else if (bIsPermanent == false)
				{
					SetTimer();
				}
				break;
			}
			case EPickupType::PT_Perception:
			{
				if (bIsPermanent == true)
				{
					Player->BaseStatsComp->IncreasePerception(IncreaseAmount);
				}
				else if (bIsPermanent == false)
				{
					SetTimer();
				}
				break;
			}
			case EPickupType::PT_Bravery:
			{
				if (bIsPermanent == true)
				{
					Player->BaseStatsComp->IncreaseBravery(IncreaseAmount);
				}
				else if (bIsPermanent == false)
				{
						SetTimer();
				}
				break;
			}
			case EPickupType::PT_Endurance:
			{
				if (bIsPermanent == true)
				{
					Player->BaseStatsComp->IncreaseEndurance(IncreaseAmount);
				}
				else if (bIsPermanent == false)
				{
					SetTimer();
				}
				break;
			}
			case EPickupType::PT_Agility:
			{
				if (bIsPermanent == true)
				{
					Player->BaseStatsComp->IncreaseAgility(IncreaseAmount);
				}
				else if (bIsPermanent == false)
				{
					SetTimer();
				}
				break;
			}
			case EPickupType::PT_Stealth:
			{
				if (bIsPermanent == true)
				{
					Player->BaseStatsComp->IncreaseStealth(IncreaseAmount);
				}
				else if (bIsPermanent == false)
				{
					SetTimer();
				}
				break;
			}
			case EPickupType::PT_Intelligence:
			{
				if (bIsPermanent == true)
				{
					Player->BaseStatsComp->IncreaseIntelligence(IncreaseAmount);
				}
				else if (bIsPermanent == false)
				{
					SetTimer();
				}
				break;
			}
			case EPickupType::PT_Luck:
			{
				if (bIsPermanent == true)
				{
					Player->BaseStatsComp->IncreaseLuck(IncreaseAmount);
				}
				else if (bIsPermanent == false)
				{
					SetTimer();
				}
				break;
			}
			case EPickupType::PT_UnarmedCombat:
			{
				if (bIsPermanent == true)
				{
					Player->BaseStatsComp->IncreaseUnarmedCombat(IncreaseAmount);
				}
				else if (bIsPermanent == false)
				{
					SetTimer();
				}
				break;
			}
			Destroy();
		}
	}
}
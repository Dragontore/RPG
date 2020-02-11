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


	CoinType = ECoinType1::CT_None;

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
	DOREPLIFETIME(ABasePickup, Weight);
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
	
	}
}

void ABasePickup::UndoStatTimer()
{
	
}

void ABasePickup::UseItem(ABaseCharacter* Player)
{
	if (Role = ROLE_Authority)
	{
	}
}

void ABasePickup::OnRep_Pickedup()
{
	
	if (Role = ROLE_Authority)
	{
		UStaticMeshComponent* Mesh = this->FindComponentByClass<UStaticMeshComponent>();
		if (Mesh)
		{

			Mesh->SetHiddenInGame(ObjectPickedup);
			this->SetActorEnableCollision(!ObjectPickedup);
		}
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
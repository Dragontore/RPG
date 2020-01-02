// Fill out your copyright notice in the Description page of Project Settings.


#include "RespawnPoints.h"

#include "Components/SphereComponent.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

#include "Game Mechanics/MainGameMode.h"
#include "Character/BaseCharacter.h"
 
ARespawnPoints::ARespawnPoints()
{
	//Default Values
	CollisonRadius = 150.f;

	CollisonSphere = CreateDefaultSubobject<USphereComponent>("Collision Sphere");
	CollisonSphere->SetupAttachment(RootComponent);
	CollisonSphere->SetSphereRadius(CollisonRadius);
	CollisonSphere->OnComponentBeginOverlap.AddDynamic(this, &ARespawnPoints::OnOverlapBegin);
}

void ARespawnPoints::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Role == ROLE_Authority)
	{
		if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
		{
			if (ABaseCharacter* Character = Cast<ABaseCharacter>(OtherActor))
			{
				AGameModeBase* BaseGamemode = GetWorld()->GetAuthGameMode();
				FVector Location = GetActorLocation();
				if (AMainGameMode* GameMode = Cast<AMainGameMode>(BaseGamemode))
				{
					UE_LOG(LogTemp, Warning, TEXT("Overlap"));
					GameMode->SetRespawnLocation(Location);
				}
				
			}
		}
	}
}

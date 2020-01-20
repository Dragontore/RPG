// Fill out your copyright notice in the Description page of Project Settings.


#include "RespawnPoints.h"

#include "Components/SphereComponent.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

#include "Game Mechanics/MainGameMode.h"
#include "Game Mechanics/MainPlayerController.h"
#include "Character/BaseCharacter.h"
#include "Kismet/GameplayStatics.h"
 
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
				AMainPlayerController* MainController = Cast<AMainPlayerController>(Character->GetController());
				if (MainController != NULL)
				{
					UE_LOG(LogTemp, Warning, TEXT("Overlap"));
					FVector Location = GetActorLocation();
					MainController->SetRespawnLocation(Location);
				}
				
			}
		}
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"

#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"

#include "TargetPoints/RespawnPoints.h"
#include "Character/BaseCharacter.h"
#include "Game Mechanics/MainPlayerController.h"

AMainGameMode::AMainGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClass(TEXT("/Game/Blueprints/Characters/Base_Character/BP_BaseCharacter"));
	if (PlayerPawnClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnClass.Class;
	}
}

void AMainGameMode::Respawn(AController* Controller)
{
	if (Controller)
	{
		if (Role == ROLE_Authority)
		{
			//TODO Set Respawn point to Target Points
				UE_LOG(LogTemp, Warning, TEXT("Function Call"));
				FVector Location = FVector(-400.0f, 50.0f, 2000.f);
				AMainPlayerController* PlayerController = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());
				if (APawn* Pawn = GetWorld()->SpawnActor<APawn>(DefaultPawnClass, PlayerController->SpawnPoint, FRotator::ZeroRotator))
				{
					Controller->Possess(Pawn);
				}
		}
	}
}

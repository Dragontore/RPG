// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"

#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

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

	PlayerControllerClass = AMainPlayerController::StaticClass();
	RespawnTimer = 5.0f;
}

void AMainGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	//TODO Possible random Spawn point. look at video 8 onwards
}

void AMainGameMode::Respawn(AController* Controller)
{
	if (Controller)
	{
		if (Role == ROLE_Authority)
		{
			//TODO Set Respawn point to Target Points

				ABaseCharacter* Character = Cast<ABaseCharacter>(Controller->GetPawn());
				AMainPlayerController* PlayerController = Cast<AMainPlayerController>(Character->GetController());
				FVector NewSpawnPoint = PlayerController->SpawnPoint;
				if (APawn* Pawn = GetWorld()->SpawnActor<ABaseCharacter>(DefaultPawnClass, NewSpawnPoint, FRotator::ZeroRotator))
				{
					UE_LOG(LogTemp, Warning, TEXT("Spawn Point : %s"), *NewSpawnPoint.ToString());
					Controller->Possess(Pawn);
				}
		}
	}
}

void AMainGameMode::Spawn(AController* Controller)
{
	if (Controller)
	{
		if (Role == ROLE_Authority)
		{
			FTimerDelegate RespawnDelegate;
			RespawnDelegate.BindUFunction(this, FName("Respawn"), Controller);
			FTimerHandle RespawnHandle;
			GetWorld()->GetTimerManager().SetTimer(RespawnHandle, RespawnDelegate, RespawnTimer, false);
		}
	}
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MainGameMode.generated.h"


/**
 * 
 */
UCLASS()
class RPG_API AMainGameMode : public AGameMode
{
	GENERATED_BODY()

public: 
	AMainGameMode();

protected:



public:

	void Respawn(AController* Controller);
	
};

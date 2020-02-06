// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/BaseInteractable.h"
#include "BaseInteractableProp.generated.h"

class UStaticMeshComponent;

/**
 * 
 */
UCLASS()
class RPG_API ABaseInteractableProp : public ABaseInteractable
{
	GENERATED_BODY()

		// Sets default values for this actor's properties
		ABaseInteractableProp();

public:
			// Non Blueprint Public Varibles
public:
			// Non Blueprint Public Functions
public:
			// Blueprint Public Varibles

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	UStaticMeshComponent* PropMeshComp;
public:
			// Blueprint Public Functions
protected:
			// Non Blueprint Protected Varibles
protected:
			// Non Blueprint Protected Functions
protected:
			// Blueprint Protected Varibles
protected:
			// Blueprint Protected Function
};

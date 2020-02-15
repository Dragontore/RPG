// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/BaseInteractable.h"
#include "BaseContainer.generated.h"

class UStaticMeshComponent;
class UInteractableInfoComponent;
class USphereComponent;
class UInventory;

UCLASS()
class RPG_API ABaseContainer : public ABaseInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseContainer();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	UStaticMeshComponent* TopMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	UInventory* Inventory;


public:	

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	UInventory* GetInventoryComponent();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};

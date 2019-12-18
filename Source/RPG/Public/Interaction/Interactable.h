// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class ABaseCharacter;

UCLASS()
class RPG_API AInteractable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractable();

public:

	//Blueprint function for inteaction use of timeline etc
	UFUNCTION(BlueprintImplementableEvent)
	void Interact(ABaseCharacter* Player);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	UStaticMeshComponent* InteractionMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	UStaticMeshComponent* HoldingMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	USphereComponent* CollisonSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collison")
	float CollisonRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")
		FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")
		FText Action;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defaults")
		FText Decription;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};

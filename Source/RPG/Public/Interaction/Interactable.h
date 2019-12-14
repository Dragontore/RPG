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
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	USphereComponent* CollisonSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collison")
	float CollisonRadius;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};

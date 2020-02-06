// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseInteractable.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class ABaseCharacter;
class UInteractableInfoComponent; // TODO Remove if polymothisim works

UCLASS()
class RPG_API ABaseInteractable : public AActor
{
	GENERATED_BODY()
	

public:	
					// Non Blueprint Public Function
	
	// Sets default values for this actor's properties
	ABaseInteractable();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
					// Non Blueprint Public Varibles

public:
					// Blueprint Public Function

	//Blueprint function for inteaction use of timeline etc
	UFUNCTION(BlueprintImplementableEvent)
	void Interact(ABaseCharacter* Player);

public:
					// Blueprint Public Variblies

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	USphereComponent* CollisonSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collison")
	float CollisonRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	UStaticMeshComponent* BaseInteractionMeshComp;

protected:
					// Non Blueprint Protected Functions

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, 
							AActor* OtherActor, 
							UPrimitiveComponent* OtherComp, 
							int32 OtherBodyIndex, 
							bool bFromSweep, 
							const FHitResult& SweepResult);

protected:
					// Non Blueprint Protected Varibles


protected: 
					// Blueprint Protected Functions

	UFUNCTION(BlueprintCallable, Category = "Interaction Info")
	FString GetUseText();

protected:
					//Blueprint Protected Varibles
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UInteractableInfoComponent* InteractableInfo;


};

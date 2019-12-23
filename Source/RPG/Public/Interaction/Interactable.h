// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class ABaseCharacter;
class UInteractableInfoComponent;

UCLASS()
class RPG_API AInteractable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractable();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UInteractableInfoComponent* InteractableInfo;

public:

	//Blueprint function for inteaction use of timeline etc
	UFUNCTION(BlueprintImplementableEvent)
	void Interact(ABaseCharacter* Player);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	USphereComponent* CollisonSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collison")
	float CollisonRadius;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	UStaticMeshComponent* InteractionMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	UStaticMeshComponent* HoldingMeshComp;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category = "Interaction Info")
	FString GetUseText();

};

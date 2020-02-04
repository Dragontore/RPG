// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseContainer.generated.h"

class UStaticMeshComponent;
class UInteractableInfoComponent;
class USphereComponent;
class UInventory;

UCLASS()
class RPG_API ABaseContainer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseContainer();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UInteractableInfoComponent* InteractableInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	USphereComponent* CollisonSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collison")
	float SphereRadius;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	UStaticMeshComponent* BaseMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	UStaticMeshComponent* TopMeshComp;

	UInventory* Inventory;


public:	

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category = "Interaction Info")
	FString GetUseText();

	//Blueprint function for inteaction use of timeline etc
	UFUNCTION(BlueprintImplementableEvent)
	void Interact(ABaseCharacter* Player);

	UFUNCTION()
	UInventory* GetInventoryComponent();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};

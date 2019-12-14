// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class ABaseCharacter;

// add struct for default value

UENUM(BlueprintType)
enum class EPickupType : uint8
{
	PT_None				UMETA(DisplayName = "None"),
	PT_Health			UMETA(DisplayName = "Health"),
	PT_Stamina			UMETA(DisplayName = "Stamina"),
	PT_Mana				UMETA(DisplayName = "Mana"),
	PT_Money			UMETA(DisplayName = "Money")
};

UCLASS()
class RPG_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

protected: 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	USphereComponent* CollisonSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float IncreaseAmount;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ENUMS")
	EPickupType PickupType;

	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void MultiDestroyActor();
	bool MultiDestroyActor_Validate();
	void MultiDestroyActor_Implementation();

public:	

	UFUNCTION()
	void UseItem(ABaseCharacter* Player);

};

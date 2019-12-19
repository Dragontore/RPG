// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class ABaseCharacter;
class UInteractableInfoComponent;

// add struct for default value

UENUM(BlueprintType)
enum class EPickupType : uint8
{
	PT_None				UMETA(DisplayName = "None"),
	PT_Health			UMETA(DisplayName = "Health"),
	PT_Stamina			UMETA(DisplayName = "Stamina"),
	PT_Mana				UMETA(DisplayName = "Mana"),
	PT_Money			UMETA(DisplayName = "Money"),
	PT_Stats			UMETA(DisplayName = "Stats")
};
UENUM(BlueprintType)
enum class ECoinType : uint8
{
	CT_None			UMETA(DisplayName = "None"),
	CT_Bronze		UMETA(DisplayName = "Bronze Coin"),
	CT_Silver		UMETA(DisplayName = "Silver Coin"),
	CT_Gold			UMETA(DisplayName = "Gold Coin")
};

UENUM(BlueprintType)
enum class EBaseStatType : uint8
{
	BT_None				UMETA(DisplayName = "None"),
	BT_Strength			UMETA(DisplayName = "Strength"),
	BT_Charm			UMETA(DisplayName = "Charm"),
	BT_Perception		UMETA(DisplayName = "Perception"),
	BT_Bravery			UMETA(DisplayName = "Bravery"),
	BT_Endurance		UMETA(DisplayName = "Endurance"),
	BT_Agility			UMETA(DisplayName = "Agility"),
	BT_Stealth			UMETA(DisplayName = "Stealth"),
	BT_Intelligence		UMETA(DisplayName = "Intelligence"),
	BT_Luck				UMETA(DisplayName = "Luck"),
	BT_UnarmedCombat	UMETA(DisplayName = "Unarmed Combat")
};

UCLASS()
class RPG_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UInteractableInfoComponent* InteractableInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
	USphereComponent* CollisonSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collison")
	float SphereRadius;

protected: 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float IncreaseAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	bool bIsPermanent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float AmountTime;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle StatsTimerHandle;
	FTimerHandle UndoStatsTimerHandle;

	void SetTimer();
	void ClearTimer();

	void HandleStatTimer();
	void UndoStatTimer();
	float Counter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ENUMS")
	EPickupType PickupType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ENUMS")
	ECoinType CoinType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ENUMS")
	EBaseStatType StatsType;

	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void MultiDestroyActor();
	bool MultiDestroyActor_Validate();
	void MultiDestroyActor_Implementation();

public:	

	UFUNCTION()
	void UseItem(ABaseCharacter* Player);

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//UFUNCTION(BlueprintCallable, Category = "Interaction Info")
	//FString GetUseText() const;
};

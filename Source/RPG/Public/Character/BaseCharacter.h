// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UBaseStatsComponent;
class ULineTrace;
class UInventory;
class UUserWidget;

UCLASS()
class RPG_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

public: //Blueprint Varibles

	// Sets default values for this character's properties
	ABaseCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	//Added Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UBaseStatsComponent* BaseStatsComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	UInventory* Inventory;
	
	TSubclassOf<UUserWidget> InventoryWidgetClass;

	UUserWidget* InventoryWidget;

public: //Non Blueprint Functions

		// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

	// Sprint Functions
	void StartSprinting();
	void StopSprinting();
	void ControlSprintingHandle();

	// Jump Functions
	void AttempJump();

public: //Non Blueprint Varibles

	//Jump Functions
	float JumpCost;

public:


protected: // Blueprint Functions

		// Sprint Functions
	UFUNCTION(BlueprintCallable, Category = "Sprint")
	float GetSprintCost();

	UFUNCTION(BlueprintCallable, Category = "Sprint")
	void IncreaseSprintCost(float sprintCostIncrease);

	UFUNCTION(BlueprintCallable, Category = "Sprint")
	void DecreaseSprintCost(float sprintCostDecrease);

	//Protected Added Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	ULineTrace* LineTraceComp;

	//Function to display Health Bar
	UFUNCTION(Blueprintpure, Category = "Stats")
	float ReturnPlayersHealth();

	// Function to display Stamina Bar
	UFUNCTION(Blueprintpure, Category = "Stats")
	float ReturnPlayerStamina();

	// Function to display Mana Bar
	UFUNCTION(Blueprintpure, Category = "Stats")
	float ReturnPlayerMana();

	//Inventory Functions
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	UInventory* GetInventoryComp();

protected://Blueprint Varibles

		// Die Varibles
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Timers")
	float DestroyTime;

	//Interact functions
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
	float LineTraceLength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interact")
	float AttackOneLength;

protected: //Non Blueprint Varibles

	//Sprint Varibles
	//TODO possible add uproperty. 
	UPROPERTY(Replicated)
	bool bIsSprinting;
	float SprintCost;
	FTimerHandle SprintingHandle;
	float SprintTime;

	// Die Varibles
	FTimerHandle DestroyHandle;

protected:// Non Blueprint Functions

	void HandleSprinting();

	//Interact functions
	void Interact();

	void OpenCloseInventory();

	//Base Attack TODO Action Bars
	void AttackOne();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerAttackOne();
	bool ServerAttackOne_Validate();
	void ServerAttackOne_Implementation();

	//die functions
	void Die();
	void CallDestroy(); //Temp Function

	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void MultiDie();
	bool MultiDie_Validate();
	void MultiDie_Implementation();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	//Sprint Server Functions

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerStartSprinting();
	bool ServerStartSprinting_Validate();
	void ServerStartSprinting_Implementation();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerStopSprinting();
	bool ServerStopSprinting_Validate();
	void ServerStopSprinting_Implementation();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerHandleSprinting();
	bool ServerHandleSprinting_Validate();
	void ServerHandleSprinting_Implementation();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerIncreaseSprintCost(float serverSprintCostIncrease);
	bool ServerIncreaseSprintCost_Validate(float serverSprintCostIncrease);
	void ServerIncreaseSprintCost_Implementation(float serverSprintCostIncrease);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerDecreaseSprintCost(float serverSprintCostDecrease);
	bool ServerDecreaseSprintCost_Validate(float serverSprintCostDecrease);
	void ServerDecreaseSprintCost_Implementation(float serverSprintCostDecrease);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerControlSprintingHandle();
	bool ServerControlSprintingHandle_Validate();
	void ServerControlSprintingHandle_Implementation();

	//Server Interact Function
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerInteract();
	bool ServerInteract_Validate();
	void ServerInteract_Implementation();

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

};

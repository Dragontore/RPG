// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h" // may need to remove
#include "GameFramework/SpringArmComponent.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "TimerManager.h"
#include "Net/UnrealNetwork.h"
#include "Components/SkeletalMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

#include "Components/BaseStatsComponent.h"
#include "Components/LineTrace.h"
#include "Game Mechanics/MainGameMode.h"
#include "Components/Inventory.h"
#include "Interaction/BaseContainer.h"
#include "Interaction/BasePickup.h"
#include "Interaction/BaseInteractable.h"
#include "Interaction/BasePotion.h"
#include "Interaction/BaseInteractableProp.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	BaseStatsComp = CreateDefaultSubobject<UBaseStatsComponent>(TEXT("Base Stats Component"));
	LineTraceComp = CreateDefaultSubobject<ULineTrace>(TEXT("Line Trace Component"));
	Inventory = CreateDefaultSubobject<UInventory>(TEXT("Inventory Component"));
	
	//static ConstructorHelpers::FClassFinder<UUserWidget> InventoryRef(TEXT("/Game/UI/Inventory/UI_Inventory"));
	//if (InventoryRef.Class)
	//{
	//	InventoryWidgetClass = InventoryRef.Class;
	//}

	//Default for Sprinting
	bIsSprinting = false;
	SprintCost = 5.f;
	SprintTime = 1.f;

	//Default For Jump
	JumpCost = 10.f;

	//Default for Interact
	LineTraceLength = 170.f;
	//Default for Attack One LineTrace
	AttackOneLength = 5000.f;
	// Default Die Timer
	DestroyTime = 10.0f; //TODO Test for best destroy Time

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	ControlSprintingHandle();
}

void ABaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate to every client, no special condition required
	//Replicated Varibles
	DOREPLIFETIME(ABaseCharacter, bIsSprinting);
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABaseCharacter::AttempJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ABaseCharacter::StartSprinting);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ABaseCharacter::StopSprinting);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABaseCharacter::MoveRight);

	//Custome Input Bindings
	PlayerInputComponent->BindAction("Action", IE_Pressed, this, &ABaseCharacter::Interact);
	//PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &ABaseCharacter::OpenCloseInventory);
	//Custome Input Attack Bindings
	PlayerInputComponent->BindAction("Attack One", IE_Pressed, this, &ABaseCharacter::AttackOne);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ABaseCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ABaseCharacter::LookUpAtRate);
}

void ABaseCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ABaseCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ABaseCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
		{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		if (!bIsSprinting)
			Value *= 0.5f;
			AddMovementInput(Direction, Value);

	}
}

void ABaseCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		if (!bIsSprinting)
			Value *= 0.5f;
			AddMovementInput(Direction, Value);

	}
}

//Custom Functions

//Sprint Function

void ABaseCharacter::StartSprinting()
{
	float CurrentStamina = BaseStatsComp->GetCurrentStamina();
	float CurrentSprintCost = GetSprintCost();
	if (Role < ROLE_Authority)
	{
		ServerStartSprinting();
	}
	else if (Role == ROLE_Authority)
	{
		if (CurrentStamina > CurrentSprintCost && !GetMovementComponent()->IsFalling())
		{
			bIsSprinting = true;
			BaseStatsComp->ControlSprintingTimer(true);
			UE_LOG(LogTemp, Warning, TEXT("Sprint Called"))
		}
		else if (CurrentStamina == 0.0f)
		{
			BaseStatsComp->ControlSprintingTimer(false);
		}
	}
}

void ABaseCharacter::StopSprinting()
{
	if (Role < ROLE_Authority)
	{
		ServerStopSprinting();
	}
	else if (Role == ROLE_Authority)
	{
		bIsSprinting = false;
		BaseStatsComp->ControlSprintingTimer(false);
	}

}

void ABaseCharacter::ControlSprintingHandle()
{
	if (Role < ROLE_Authority)
	{
		ServerControlSprintingHandle();
	}
	else if (Role == ROLE_Authority)
	{
		GetWorld()->GetTimerManager().SetTimer(SprintingHandle, this, &ABaseCharacter::HandleSprinting, SprintTime, true);
	}
}

void ABaseCharacter::HandleSprinting()
{
	if (Role < ROLE_Authority)
	{
		ServerHandleSprinting();
	}
	else if (Role == ROLE_Authority)
	{
		if (bIsSprinting && this->GetVelocity().Size())
		{
			BaseStatsComp->DecreaseCurrentStamina(SprintCost);
		}
	}
}

float ABaseCharacter::GetSprintCost()
{
	return SprintCost;
}

void ABaseCharacter::IncreaseSprintCost(float sprintCostIncrease)
{
	if (Role < ROLE_Authority)
	{
		ServerIncreaseSprintCost(sprintCostIncrease);
	}
	else if (Role == ROLE_Authority)
	{
		SprintCost += sprintCostIncrease;
	}
}

void ABaseCharacter::DecreaseSprintCost(float sprintCostDecrease)
{
	if (Role < ROLE_Authority)
	{
		ServerDecreaseSprintCost(sprintCostDecrease);
	}
	else if (Role == ROLE_Authority)
	{
		SprintCost -= sprintCostDecrease;
	}
}

bool ABaseCharacter::ServerIncreaseSprintCost_Validate(float serverSprintCostIncrease)
{
	return true;
}

void ABaseCharacter::ServerIncreaseSprintCost_Implementation(float serverSprintCostIncrease)
{
	if (Role == ROLE_Authority)
	{
		IncreaseSprintCost(serverSprintCostIncrease);
	}
}

bool ABaseCharacter::ServerDecreaseSprintCost_Validate(float serverSprintCostDecrease)
{
	return true;
}

void ABaseCharacter::ServerDecreaseSprintCost_Implementation(float serverSprintCostDecrease)
{
	if (Role == ROLE_Authority)
	{

		DecreaseSprintCost(serverSprintCostDecrease);
	}
}

bool ABaseCharacter::ServerControlSprintingHandle_Validate()
{
	return true;
}

void ABaseCharacter::ServerControlSprintingHandle_Implementation()
{
	if (Role == ROLE_Authority)
	{
		ControlSprintingHandle();
	}
}

bool ABaseCharacter::ServerStartSprinting_Validate()
{
	return true;
}

void ABaseCharacter::ServerStartSprinting_Implementation()
{
	if (Role == ROLE_Authority)
	{
		StartSprinting();
	}
}
bool ABaseCharacter::ServerStopSprinting_Validate()
{
	return true;
}

void ABaseCharacter::ServerStopSprinting_Implementation()
{
	if (Role == ROLE_Authority)
	{
		StopSprinting();
	}
}

bool ABaseCharacter::ServerHandleSprinting_Validate()
{
	return true;
}

void ABaseCharacter::ServerHandleSprinting_Implementation()
{
	if (Role == ROLE_Authority)
	{
		HandleSprinting();
	}
}

//Jump Function

void ABaseCharacter::AttempJump()
{
	if (BaseStatsComp->GetCurrentStamina() > JumpCost && !GetMovementComponent()->IsFalling())
	{
		Jump();
		StopSprinting();
		BaseStatsComp->DecreaseCurrentStamina(JumpCost);
	}
}

//Inventory Functions

//void ABaseCharacter::OpenCloseInventory()
//{
//	if (InventoryWidget && InventoryWidget->IsInViewport())
//	{
//		InventoryWidget->RemoveFromViewport();
//		if (APlayerController* PController = GetController()->CastToPlayerController())
//		{
//			PController->bShowMouseCursor = false;
//			PController->SetInputMode(FInputModeGameOnly());
//		}
//	}
//	else
//	{
//		InventoryWidget = CreateWidget<UUserWidget>(GetWorld(), InventoryWidgetClass);
//		if (InventoryWidget)
//		{
//			InventoryWidget->AddToViewport();
//			if (APlayerController* PController = GetController()->CastToPlayerController())
//			{
//				PController->bShowMouseCursor = true;
//				PController->SetInputMode(FInputModeGameAndUI());
//			}
//		}
//	}
//}

//Interact Function

void ABaseCharacter::Interact()
{
	//TODO Set else if to switch statment

	FVector StartTrace = GetMesh()->GetBoneLocation(FName("head"));
	FVector EndTrace = StartTrace + FollowCamera->GetForwardVector() * LineTraceLength;
	FHitResult HitResult = LineTraceComp->LineTraceSingle(StartTrace, EndTrace, true);
	if (AActor* Actor = HitResult.GetActor())
	{

		if (ABasePotion* Potion = Cast<ABasePotion>(Actor))
		{
			ServerInteract();
		}
		else if (ABaseInteractableProp* InteractableProp = Cast<ABaseInteractableProp>(Actor))
		{
			ServerInteract();
		}
		else if (ABaseContainer* Container = Cast<ABaseContainer>(Actor))// TODO Change code
		{
			OpenedContainer = Container;
			OpenCloseInventory();
			//TODO Check to move If Statment To server Interact.
			ServerInteract();
			if (UInventory* ContainerInventory = Container->GetInventoryComponent())
			{
				TArray<ABasePickup*> ContainerItems = ContainerInventory->GetInventoryItem();
				for (ABasePickup* Pickup : ContainerItems)
				{
					UE_LOG(LogTemp, Warning, TEXT("Function Call"));
				}
			}
		}
	}
}

bool ABaseCharacter::ServerInteract_Validate()
{
	return true;
}

void ABaseCharacter::ServerInteract_Implementation()
{
	if (Role == ROLE_Authority)
	{
		FVector StartTrace = GetMesh()->GetBoneLocation(FName("head"));
		FVector EndTrace = StartTrace + FollowCamera->GetForwardVector() * LineTraceLength;
		FHitResult HitResult = LineTraceComp->LineTraceSingle(StartTrace, EndTrace, true);
		if (AActor* Actor = HitResult.GetActor())
		{
			if (ABasePotion* Potion = Cast<ABasePotion>(Actor))
			{
				Potion->Interact(this);
				if (Inventory->GetInventoryCount() < Inventory->GetInventorySlotsAmout())
				{
					Inventory->AddItem(Potion);
				}
			}
			else if (ABaseInteractable* Interactable = Cast<ABaseInteractable>(Actor))
			{
				Interactable->Interact(this);
			}
			else if (ABaseContainer* Container = Cast<ABaseContainer>(Actor))
			{
				Container->Interact(this);
			}
		}
	}
}

//Attack Function

void ABaseCharacter::AttackOne()
{
	FVector StartTrace = GetMesh()->GetBoneLocation(FName("head"));
	FVector EndTrace = StartTrace + FollowCamera->GetForwardVector() * AttackOneLength;
	FHitResult HitResult = LineTraceComp->LineTraceSingle(StartTrace, EndTrace, true);
	if (AActor* Actor = HitResult.GetActor())
	{
		if (ABaseCharacter* Character = Cast<ABaseCharacter>(Actor))
		{
			ServerAttackOne();
		}
	}
}

bool ABaseCharacter::ServerAttackOne_Validate()
{
	return true;
}

void ABaseCharacter::ServerAttackOne_Implementation()
{
	if (Role == ROLE_Authority)
	{
		FVector StartTrace = GetMesh()->GetBoneLocation(FName("head"));
		FVector EndTrace = StartTrace + FollowCamera->GetForwardVector() * AttackOneLength;
		FHitResult HitResult = LineTraceComp->LineTraceSingle(StartTrace, EndTrace, true);
		if (AActor* Actor = HitResult.GetActor())
		{
			if (ABaseCharacter* Character = Cast<ABaseCharacter>(Actor))
			{
				float TestDamage = 20.f; // TODO Remove and action Actual Damage
				Character->TakeDamage(TestDamage, FDamageEvent(), GetController(), this);
			}
		}
	}
}

//Damage Functions

float ABaseCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (Role < ROLE_Authority || BaseStatsComp->GetCurrentHealth() <= 0.0f)
	{
		return 0.0f;
	}
	// Call the base class - this will tell us how much damage to apply  
	const float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	if (ActualDamage > 0.0f)
	{
		BaseStatsComp->DecreaseCurrentHealth(ActualDamage);
		if (BaseStatsComp->GetCurrentHealth() <= 0)
		{
			Die();

		}
	}
	return ActualDamage;
}

//Temp Function
void ABaseCharacter::CallDestroy()
{
	if (Role == ROLE_Authority)
	{
		Destroy();
	}
}

//Die Funtions

void ABaseCharacter::Die()
{
	if (Role == ROLE_Authority)
	{
		Inventory->DropAllItems();
		MultiDie();
		AGameModeBase* BaseGameMode = GetWorld()->GetAuthGameMode();
		if (AMainGameMode* GameMode = Cast<AMainGameMode>(BaseGameMode))
		{
			GameMode->Spawn(GetController());
		}

		// Start Destroy Timer
		GetWorld()->GetTimerManager().SetTimer(DestroyHandle, this, &ABaseCharacter::CallDestroy, DestroyTime, false);
	}
}

bool ABaseCharacter::MultiDie_Validate()
{
	return true;
}

void ABaseCharacter::MultiDie_Implementation()
{
	// TODO Play Anim Montage of death
	//Rag Doll
	this->GetCapsuleComponent()->DestroyComponent();
	this->GetCharacterMovement()->DisableMovement();
	this->GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	this->GetMesh()->SetAllBodiesSimulatePhysics(true);
}

//Getters

float ABaseCharacter::ReturnPlayersHealth()
{
	float RetCurrentHealth = BaseStatsComp->GetCurrentHealth();
	float RetMaxHealth = BaseStatsComp->GetMaxHealth();

	float RetHealth = RetCurrentHealth / RetMaxHealth;
	return RetHealth;
}
float ABaseCharacter::ReturnPlayerStamina()
{
	float RetCurrentStamina = BaseStatsComp->GetCurrentStamina();
	float RetMaxStamina = BaseStatsComp->GetMaxStamina();

	float RetStamina = RetCurrentStamina / RetMaxStamina;

	return RetStamina;
}

float ABaseCharacter::ReturnPlayerMana()
{
	float RetCurrentMana = BaseStatsComp->GetCurrentMana();
	float RetMaxMana = BaseStatsComp->GetMaxMana();

	float RetMana = RetCurrentMana / RetMaxMana;

	return RetMana;
}

UInventory* ABaseCharacter::GetInventoryComp()
{
	return Inventory;
}

ABaseContainer* ABaseCharacter::GetBaseContainer()
{
	return OpenedContainer;
}

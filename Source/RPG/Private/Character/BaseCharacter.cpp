// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h" // may need to remove
#include "GameFramework/SpringArmComponent.h"
#include "Engine/World.h"

#include "Components/BaseStatsComponent.h"

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

	//Default for Sprinting
	bIsSprinting = false;
	SprintCost = 5.f;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ABaseCharacter::StartSprinting);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ABaseCharacter::StopSprinting);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABaseCharacter::MoveRight);

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
		AddMovementInput(Direction, Value);
	}
}

void ABaseCharacter::StartSprinting()
{
	float CurrentStamina = BaseStatsComp->GetCurrentStamina();
	float CurrentSprintCost = GetSprintCost();

	if (CurrentStamina > CurrentSprintCost)
	{
		bIsSprinting = true;
		BaseStatsComp->DecreaseCurrentStamina(CurrentSprintCost);
	}
}

void ABaseCharacter::StopSprinting()
{
	bIsSprinting = false;
	BaseStatsComp->IncreaseCurrentStamina(1.f);
}

float ABaseCharacter::GetSprintCost()
{
	return SprintCost;
}

void ABaseCharacter::IncreaseSprintCost(float sprintCostIncrease)
{
	if (Role < ROLE_Authority)
	{

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
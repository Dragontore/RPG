// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseInteractable.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Net/UnrealNetwork.h"

#include "Components/InteractableInfoComponent.h"
#include "Character/BaseCharacter.h"

// Sets default values
ABaseInteractable::ABaseInteractable()
{
	//Default Values
	CollisonRadius = 150.f;

	bReplicates = true;

	BaseInteractionMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Base Interaction Mesh");
	RootComponent = BaseInteractionMeshComp;

	CollisonSphere = CreateDefaultSubobject<USphereComponent>("Collision Sphere");
	CollisonSphere->SetupAttachment(BaseInteractionMeshComp);
	CollisonSphere->SetSphereRadius(CollisonRadius);

	InteractableInfo = CreateDefaultSubobject<UInteractableInfoComponent>(TEXT("Interactable Info"));

}

// Called when the game starts or when spawned
void ABaseInteractable::BeginPlay()
{
	Super::BeginPlay();

	if (Role == ROLE_Authority)
	{
		SetReplicates(true);
	}
	
}

void ABaseInteractable::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if (ABaseCharacter* Character = Cast<ABaseCharacter>(OtherActor))
		{

		}
	}
}

FString ABaseInteractable::GetUseText()
{
	return FString::Printf(TEXT("%s : Press E To : %s"), *InteractableInfo->GetName(), *InteractableInfo->GetAction());
}


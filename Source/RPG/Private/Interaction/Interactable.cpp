// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Net/UnrealNetwork.h"

#include "Components/InteractableInfoComponent.h"
#include "Character/BaseCharacter.h"


// Sets default values
AInteractable::AInteractable()
{
	//Default Values
	CollisonRadius = 150.f;

	bReplicates = true;

	InteractionMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Interaction Mesh");
	RootComponent = InteractionMeshComp;

	CollisonSphere = CreateDefaultSubobject<USphereComponent>("Collision Sphere");
	CollisonSphere->SetupAttachment(InteractionMeshComp);
	CollisonSphere->SetSphereRadius(CollisonRadius);

	HoldingMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Interaction Mesh Holder");
	HoldingMeshComp->SetupAttachment(InteractionMeshComp);

	InteractableInfo = CreateDefaultSubobject<UInteractableInfoComponent>(TEXT("Interactable Info"));


}

// Called when the game starts or when spawned
void AInteractable::BeginPlay()
{
	Super::BeginPlay();

	if (Role == ROLE_Authority)
	{
		SetReplicates(true);
	}


	
}

void AInteractable::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if (ABaseCharacter* Character = Cast<ABaseCharacter>(OtherActor))
		{

		}
	}
}

FString AInteractable::GetUseText()
{
	return FString::Printf(TEXT("%s : Press E To : %s"), *InteractableInfo->GetName(), *InteractableInfo->GetAction());
}



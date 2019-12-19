// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Net/UnrealNetwork.h"

#include "Components/InteractableInfoComponent.h"


// Sets default values
AInteractable::AInteractable()
{

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
	SetReplicates(true);

	//Default Values
	CollisonRadius = 150.f;
	
}



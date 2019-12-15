// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AInteractable::AInteractable()
{

	bReplicates = true;

	InteractionMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Interaction Mesh");
	RootComponent = InteractionMeshComp;

	CollisonSphere = CreateDefaultSubobject<USphereComponent>("Collision Sphere");
	CollisonSphere->SetupAttachment(InteractionMeshComp);
	CollisonSphere->InitSphereRadius(CollisonRadius);

	HoldingMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Interaction Mesh Holder");
	HoldingMeshComp->SetupAttachment(InteractionMeshComp);

	//Default Values
	CollisonRadius = 500.f;
}

// Called when the game starts or when spawned
void AInteractable::BeginPlay()
{
	Super::BeginPlay();
	SetReplicates(true);
	
}



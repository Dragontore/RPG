// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AInteractable::AInteractable()
{

	bReplicates = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = MeshComp;

	CollisonSphere = CreateDefaultSubobject<USphereComponent>("Collision Sphere");
	CollisonSphere->SetupAttachment(MeshComp);
	CollisonSphere->InitSphereRadius(CollisonRadius);

	//Default Values
	CollisonRadius = 500.f;
}

// Called when the game starts or when spawned
void AInteractable::BeginPlay()
{
	Super::BeginPlay();
	SetReplicates(true);
	
}



// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
APickup::APickup()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = MeshComp;

	CollisonSphere = CreateDefaultSubobject<USphereComponent>("Collision Sphere");
	CollisonSphere->SetupAttachment(MeshComp);
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
}




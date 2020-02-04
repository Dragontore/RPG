// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseContainer.h"

#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Net/UnrealNetwork.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

#include "Character/BaseCharacter.h"
#include "Components/InteractableInfoComponent.h"
#include "Components/Inventory.h"

// Sets default values
ABaseContainer::ABaseContainer()
{

	SphereRadius = 150.f;
	BaseMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Base Mesh");
	RootComponent = BaseMeshComp;

	TopMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Top Mesh");
	TopMeshComp->SetupAttachment(BaseMeshComp);

	CollisonSphere = CreateDefaultSubobject<USphereComponent>("Collision Sphere");
	CollisonSphere->SetupAttachment(BaseMeshComp);
	CollisonSphere->SetSphereRadius(SphereRadius);
	CollisonSphere->OnComponentBeginOverlap.AddDynamic(this, &ABaseContainer::OnOverlapBegin);

	InteractableInfo = CreateDefaultSubobject<UInteractableInfoComponent>(TEXT("Interactable Info"));
	Inventory = CreateDefaultSubobject<UInventory>(TEXT("Inventory component"));

	bReplicates = true;

}

// Called when the game starts or when spawned
void ABaseContainer::BeginPlay()
{
	Super::BeginPlay();
	
}


void ABaseContainer::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if (ABaseCharacter* Character = Cast<ABaseCharacter>(OtherActor))
		{

		}
	}
}


FString ABaseContainer::GetUseText()
{
	return FString::Printf(TEXT("%s : Press E To : %s"), *InteractableInfo->GetName(), *InteractableInfo->GetAction());
}

UInventory* ABaseContainer::GetInventoryComponent()
{
	return Inventory;
}
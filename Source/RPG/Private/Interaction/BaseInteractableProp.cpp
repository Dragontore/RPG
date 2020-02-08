// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseInteractableProp.h"

#include "Components/StaticMeshComponent.h"



ABaseInteractableProp::ABaseInteractableProp()
{
	PropMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Prop Mesh");
	PropMeshComp->SetupAttachment(RootComponent);
}
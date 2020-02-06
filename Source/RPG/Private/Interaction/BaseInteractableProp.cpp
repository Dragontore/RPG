// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseInteractableProp.h"



ABaseInteractableProp::ABaseInteractableProp()
{
	PropMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Prop Mesh");
}
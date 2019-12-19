// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableInfoComponent.h"

// Sets default values for this component's properties
UInteractableInfoComponent::UInteractableInfoComponent()
{

}


// Called when the game starts
void UInteractableInfoComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

FString UInteractableInfoComponent::GetName()
{
	return Name;
}

FString UInteractableInfoComponent::GetAction()
{
	return Action;
}

FString UInteractableInfoComponent::GetDecription()
{
	return Decription;
}





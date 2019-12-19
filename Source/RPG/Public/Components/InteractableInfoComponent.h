// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableInfoComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_API UInteractableInfoComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractableInfoComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	UFUNCTION(BlueprintCallable, Category = "Interactable Info")
	FString GetName();

	UFUNCTION(BlueprintCallable, Category = "Interactable Info")
	FString GetAction();

	UFUNCTION(BlueprintCallable, Category = "Interactable Info")
	FString GetDecription();

protected:

	UPROPERTY(EditAnywhere, Category = "Interactable Info")
	FString Name;
		
	UPROPERTY(EditAnywhere, Category = "Interactable Info")
	FString Action;

	UPROPERTY(EditAnywhere, Category = "Interactable Info")
	FString Decription;
};

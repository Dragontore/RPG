// Fill out your copyright notice in the Description page of Project Settings.


#include "LineTrace.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "DrawDebugHelpers.h"

#include "..\..\Public\Components\LineTrace.h"

// Sets default values for this component's properties
ULineTrace::ULineTrace()
{


	// ...
}


// Called when the game starts
void ULineTrace::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

AActor* ULineTrace::LineTraceSingle(FVector Start, FVector End)
{
	FHitResult HitResult;
	FCollisionObjectQueryParams ObjectQueryParams;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(GetOwner());

	if (GetWorld()->LineTraceSingleByObjectType(OUT HitResult, Start, End, ObjectQueryParams, QueryParams))
	{
		return HitResult.GetActor();
	}
	else
	{
		return nullptr;
	}
}

AActor* ULineTrace::LineTraceSingle(FVector Start, FVector End, bool ShowDebugLine)
{
	AActor* Actor = LineTraceSingle(Start, End);
	if (ShowDebugLine)
	{
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 3.0f, 0, 5.0f);
	}
	return Actor;
}



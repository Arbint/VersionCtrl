// Fill out your copyright notice in the Description page of Project Settings.

#include "PositionReporter.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UPositionReporter::UPositionReporter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPositionReporter::BeginPlay()
{
	Super::BeginPlay();

	// ...
	FString OwnerName = GetOwner()->GetName();
	FString ObjectPos = "X = Something, Y = something, else, etc";
	FVector OwnerLocation = GetOwner()->GetActorLocation();
	UE_LOG(LogTemp, Warning, TEXT("%s is at X: %d, Y: %d, Z: %d"), *OwnerName,OwnerLocation.X, OwnerLocation.Y, OwnerLocation.Z);
}


// Called every frame
void UPositionReporter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


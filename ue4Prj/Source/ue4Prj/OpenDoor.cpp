// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerVolume.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	// ...
	Onwer = GetOwner();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	MonitorTrigger();
}

void UOpenDoor::MonitorTrigger()
{
	
	if (getWeightInPlate() >= OpeningWeight)
	{
		OpenDoor();
		lastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	float currentTime = GetWorld()->GetTimeSeconds();
	if (currentTime - lastDoorOpenTime >= DoorCloseDelay)
	{
		CloseDoor();
	}
}

void UOpenDoor::OpenDoor()
{
	//Onwer->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
	OnDoorOpenRequest.Broadcast();
}

void UOpenDoor::CloseDoor()
{
	//Onwer->SetActorRotation(FRotator(0.0f, -90.0f, 0.0f));
	OnDoorCloseRequest.Broadcast();
}

float UOpenDoor::getWeightInPlate()
{
	float weight = 0.0f;
	TArray<AActor*> ActorsInPlate;
	PressurePlate->GetOverlappingActors(ActorsInPlate);
	for (auto& item : ActorsInPlate)
	{
		TArray<UPrimitiveComponent*> PrimatrivesInActor; 
		item->GetComponents<UPrimitiveComponent>(PrimatrivesInActor);
		for (auto& primitiveComp : PrimatrivesInActor)
		{
			if (primitiveComp->IsSimulatingPhysics())
			{
				weight += primitiveComp->GetMass();
			}
		}
	}
	return weight;
}


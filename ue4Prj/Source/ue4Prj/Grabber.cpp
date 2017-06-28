// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "C_DefaultPawn.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	UE_LOG(LogTemp, Warning, TEXT("Grabber Report For Duty"));
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	lineTraceForward();
	// ...
}

APawn* UGrabber::GetPawnOnwer()
{
	return (APawn*)GetOwner();
}

void UGrabber::GetPawnViewPoint(FVector& OutLocation, FRotator& OutRotation)
{
	APawn* OnwningPawn = GetPawnOnwer();
	
	if (OnwningPawn)
	{
		APlayerController* controller = (APlayerController*)OnwningPawn->GetController();
		if (controller)
		{
			controller->GetPlayerViewPoint(OutLocation, OutRotation);
		}
	}
}

void UGrabber::PrintPawnViewPoint()
{
	FVector Location{};
	FRotator Rotator{};
	GetPawnViewPoint(Location, Rotator);
	FString PawnLocation = Location.ToString();
	FString PawnRotation = Rotator.ToString();
	UE_LOG(LogTemp, Warning, TEXT("Location: %s"), *PawnLocation)
	UE_LOG(LogTemp, Warning, TEXT("Rotation: %s"), *PawnRotation)
}

void UGrabber::lineTraceForward()
{
	FVector PlayerLocaiton{};
	FRotator PlayerRotator{};
	GetPawnViewPoint(PlayerLocaiton, PlayerRotator);
	FVector playerForwardDirection = PlayerRotator.Vector();
	FHitResult Hit;
	FCollisionQueryParams QueryParams( "PickUpTracing", false, GetOwner() );

	bool bTracedSomething = GetWorld()->LineTraceSingleByChannel(
		Hit,
		PlayerLocaiton,
		PlayerLocaiton + playerForwardDirection * TracingReach,
		ECC_PlayerTracing,
		QueryParams
		);
	if (bDrawTracingDebugLine)
	{
		DrawDebugLine(GetWorld(), 
			PlayerLocaiton, 
			PlayerLocaiton + playerForwardDirection * TracingReach, 
			FColor::Red, 
			false,
			-1.f,
			0, 5.0f);
	}
	if (bTracedSomething)
	{
		FString HitActorName = Hit.GetActor()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("The actors name is: %s"), *HitActorName)
	}
}
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
	GatherOwnerInfo();
	setupInputComponent();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}

APawn* UGrabber::GetPawnOnwer() const
{
	return (APawn*)GetOwner();
}

void UGrabber::GetPawnViewPoint(FVector& OutLocation, FRotator& OutRotation) const
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

void UGrabber::GetFirstPickableInReach(FHitResult& hit) const
{
	FVector PlayerLocaiton{};
	FRotator PlayerRotator{};
	GetPawnViewPoint(PlayerLocaiton, PlayerRotator);
	FVector playerForwardDirection = PlayerRotator.Vector();
	FCollisionQueryParams QueryParams( "PickUpTracing", false, GetOwner() );

	bool bTracedSomething = GetWorld()->LineTraceSingleByChannel(
		hit,
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
		FString HitActorName = hit.GetActor()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("The actors name is: %s"), *HitActorName)
	}
}

void UGrabber::setupInputComponent()
{
	//bind action
	pawnInputComp->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	pawnInputComp->BindAction("Grab", IE_Released, this, &UGrabber::GrabRelease);
}

void UGrabber::Grab()
{
	//UE_LOG(LogTemp, Warning, TEXT("Grabing"));
	FHitResult hit;
	GetFirstPickableInReach(hit);
}

void UGrabber::GrabRelease()
{
	//UE_LOG(LogTemp, Warning, TEXT("Grab Released"));
}

void UGrabber::GatherOwnerInfo()
{
	pawnPhysicsHandleComp = GetOwnerComp<UPhysicsHandleComponent>();
	pawnInputComp = GetOwnerComp<UInputComponent>();

}


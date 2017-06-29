// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "C_DefaultPawn.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"

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
	UpdateGrabedObject();
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

bool UGrabber::GetFirstPickableInReach(FHitResult& hit) const
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
	return bTracedSomething;
}

void UGrabber::setupInputComponent()
{
	//bind action
	pawnInputComp->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	pawnInputComp->BindAction("Grab", IE_Released, this, &UGrabber::GrabRelease);
}

void UGrabber::Grab()
{
	FHitResult hit;
	if (GetFirstPickableInReach(hit))
	{
		UPrimitiveComponent* hitedComponent = hit.GetComponent();
		pawnPhysicsHandleComp->GrabComponent(hitedComponent,
			NAME_None,
			hitedComponent->GetOwner()->GetActorLocation(),
			true
		);
	}
}

void UGrabber::GrabRelease()
{
	pawnPhysicsHandleComp->ReleaseComponent();
}

void UGrabber::GatherOwnerInfo()
{
	pawnPhysicsHandleComp = GetOwnerComp<UPhysicsHandleComponent>();
	pawnInputComp = GetOwnerComp<UInputComponent>();

}

void UGrabber::UpdateGrabedObject()
{
	if (pawnPhysicsHandleComp->GrabbedComponent)
	{
		FVector PawnLocaiton;
		FRotator PawnRotation;
		GetPawnViewPoint(PawnLocaiton, PawnRotation);
		FVector TraceEnd = PawnLocaiton + PawnRotation.Vector() * TracingReach;
		pawnPhysicsHandleComp->SetTargetLocation(TraceEnd);
	}
}


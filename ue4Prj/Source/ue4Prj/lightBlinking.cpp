// Fill out your copyright notice in the Description page of Project Settings.

#include "lightBlinking.h"
#include "GameFramework/Actor.h"
#include "Engine/Light.h"
#include "Components/LightComponent.h"

// Sets default values for this component's properties
UlightBlinking::UlightBlinking()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	LightIntensityTimeLine = CreateDefaultSubobject<UTimelineComponent>("Light");
	LightIntensityBinder.BindUFunction(this, FName(TEXT("LightIntensityBindFunc")));
	// ...
	}


// Called when the game starts
void UlightBlinking::BeginPlay()
{
	Super::BeginPlay();
	LightIntensityTimeLine->AddInterpFloat(LightIntensityCurveFloat, LightIntensityBinder);

	LightIntensityTimeLine->Play();
	LightIntensityTimeLine->SetLooping(true);
	
	// ...
	
}


// Called every frame
void UlightBlinking::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

ALight* UlightBlinking::getOwnerAsLight()
{
	AActor* Owner = GetOwner();
	if (Owner)
	{
		ALight* OwnerAsLight = (ALight*)Owner;
		return OwnerAsLight;
	}
	return nullptr;
}

void UlightBlinking::LightIntensityBindFunc(float value)
{
	ALight* OwnerLight = getOwnerAsLight();
	UE_LOG(LogTemp, Warning, TEXT("Your message %d"), value);
	if (OwnerLight)
	{
		OwnerLight->GetLightComponent()->SetIntensity(value);
		OwnerLight->AddActorLocalOffset(FVector(value, value, value));
	}
}


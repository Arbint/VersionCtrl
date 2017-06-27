// Fill out your copyright notice in the Description page of Project Settings.

#include "blinkingLight.h"
#include "Components/SpotLightComponent.h"
#include "Components/LightComponent.h"

// Sets default values
AblinkingLight::AblinkingLight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComp = CreateDefaultSubobject<USceneComponent>("RootComp");
	RootComponent = RootComp;
	LightComp = CreateDefaultSubobject<USpotLightComponent>("Light");
	LightComp->SetupAttachment(RootComp);
	IntensityTimeLine = CreateDefaultSubobject<UTimelineComponent>("IntensityTimeLine");
	IntensityTimelineBinder.BindUFunction(this, FName("LightIntensityUpdate"));
}

// Called when the game starts or when spawned
void AblinkingLight::BeginPlay()
{
	Super::BeginPlay();
	IntensityTimeLine->AddInterpFloat(IntensityCurve, IntensityTimelineBinder);
	IntensityTimeLine->Play();
}

// Called every frame
void AblinkingLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AblinkingLight::LightIntensityUpdate(float value)
{
	UE_LOG(LogTemp, Warning, TEXT("Your message %d"), value);
}


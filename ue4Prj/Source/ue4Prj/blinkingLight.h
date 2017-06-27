// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "Curves/CurveFloat.h"
#include "blinkingLight.generated.h"

class USpotLightComponent;

UCLASS()
class UE4PRJ_API AblinkingLight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AblinkingLight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY()
		USceneComponent* RootComp;
	UPROPERTY(EditAnywhere)
		USpotLightComponent* LightComp;
	UTimelineComponent* IntensityTimeLine;
	UPROPERTY(EditAnywhere)
		UCurveFloat* IntensityCurve;
	FOnTimelineFloat IntensityTimelineBinder;
	UFUNCTION()
		void LightIntensityUpdate(float value);
	
};

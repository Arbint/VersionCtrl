// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/TimelineComponent.h"
#include "lightBlinking.generated.h"


class ALight;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4PRJ_API UlightBlinking : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UlightBlinking();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	ALight* getOwnerAsLight();

	//Use Timeline:
	UTimelineComponent* LightIntensityTimeLine;
	UPROPERTY(EditAnywhere)
		UCurveFloat* LightIntensityCurveFloat;
	FOnTimelineFloat LightIntensityBinder;
	UFUNCTION()
		void LightIntensityBindFunc(float value);
};

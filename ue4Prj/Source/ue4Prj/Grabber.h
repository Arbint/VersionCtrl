// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Pawn.h"
#include "Grabber.generated.h"
class AC_DefaultPawn;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4PRJ_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	APawn* GetPawnOnwer();

private:
	void GetPawnViewPoint(FVector& OutLocation, FRotator& OutRotation);
	void PrintPawnViewPoint();
	void lineTraceForward();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Functionality")
	bool bDrawTracingDebugLine = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Functionality")
	float TracingReach = 50.0f;

};

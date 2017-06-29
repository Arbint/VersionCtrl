// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"
class ATriggerVolume;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorRequest);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4PRJ_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();
	void CloseDoor();
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Functionality")
		float OpeningWeight = 50.0f;
	UPROPERTY(BlueprintAssignable)
		FDoorRequest OnDoorOpenRequest;
	UPROPERTY(BlueprintAssignable)
		FDoorRequest OnDoorCloseRequest;
private:
	UPROPERTY(VisibleAnywhere)
		float OpenAngle = 90.0f;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate;

	UFUNCTION()
		void MonitorTrigger();
		

	UPROPERTY(EditAnywhere)
		float DoorCloseDelay = 1;
	UPROPERTY()
		float lastDoorOpenTime;
	AActor* Onwer;
	
private:
	float getWeightInPlate();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Pawn.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Grabber.generated.h"
class AC_DefaultPawn;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4PRJ_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Functionality")
	bool bDrawTracingDebugLine = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Functionality")
	float TracingReach = 50.0f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	APawn* GetPawnOnwer() const;
	void GetPawnViewPoint(FVector& OutLocation, FRotator& OutRotation) const;
	void PrintPawnViewPoint();
	bool GetFirstPickableInReach(FHitResult& hit) const;
	void setupInputComponent();
	void Grab();
	void GrabRelease();
	void GatherOwnerInfo();
	void UpdateGrabedObject();
	UPhysicsHandleComponent* pawnPhysicsHandleComp = nullptr;
	UInputComponent* pawnInputComp = nullptr;
//template class for getting different component from owner
private:
	template<typename T>
	T* UGrabber::GetOwnerComp()
	{
		AActor* Owner = GetOwner();
		if (Owner)
		{
			T* component = Owner->FindComponentByClass<T>();
			if (component)
			{
				UE_LOG(LogTemp, Warning, TEXT("Component Found!!"));
				return component;
			}
		}
		UE_LOG(LogTemp, Error, TEXT("%s don't have the Component..."), *Owner->GetName());
		return nullptr;
	}
};



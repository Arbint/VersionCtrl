// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DefaultPawn.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Camera/CameraComponent.h"
#include "C_DefaultPawn.generated.h"

class UGrabber;
/**
 * 
 */
UCLASS()
class UE4PRJ_API AC_DefaultPawn : public ADefaultPawn
{
	GENERATED_BODY()
public:
	AC_DefaultPawn();
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fuctionlaity")
	UGrabber* GrabberComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fucntionlaity")
	UPhysicsHandleComponent* PhysicsHadleComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Viewing")
	UCameraComponent* playerEye;
};

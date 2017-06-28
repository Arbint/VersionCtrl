// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DefaultPawn.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fuctionlaity")
	UGrabber* GrabberComponent;
	
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#include "C_DefaultPawn.h"
#include "Components/SphereComponent.h"
#include "Grabber.h"



AC_DefaultPawn::AC_DefaultPawn()
{
	GrabberComponent = CreateDefaultSubobject<UGrabber>("GrabberComponent");
	PhysicsHadleComp = CreateDefaultSubobject<UPhysicsHandleComponent>("PhysicsHadleComp");
	playerEye = CreateDefaultSubobject<UCameraComponent>("PlayerEye");
	playerEye->SetupAttachment(RootComponent);
	playerEye->bUsePawnControlRotation = true;
	GetCollisionComponent()->SetSimulatePhysics(true);
	GetCollisionComponent()->SetMassOverrideInKg(NAME_None, 70.0f);
	GetCollisionComponent()->SetNotifyRigidBodyCollision(true);
	GetCollisionComponent()->bGenerateOverlapEvents = true;

}

void AC_DefaultPawn::BeginPlay()
{
	Super::BeginPlay();
}

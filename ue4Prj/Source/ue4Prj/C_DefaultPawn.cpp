// Fill out your copyright notice in the Description page of Project Settings.

#include "C_DefaultPawn.h"
#include "Grabber.h"



AC_DefaultPawn::AC_DefaultPawn()
{
	GrabberComponent = CreateDefaultSubobject<UGrabber>("GrabberComponent");
	PhysicsHadleComp = CreateDefaultSubobject<UPhysicsHandleComponent>("PhysicsHadleComp");
}

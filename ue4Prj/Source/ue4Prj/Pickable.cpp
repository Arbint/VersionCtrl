// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickable.h"


// Sets default values
APickable::APickable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	VisualMesh->SetCollisionResponseToChannel(ECC_PlayerTracing, ECR_Block);
	VisualMesh->SetMobility(EComponentMobility::Movable);
	VisualMesh->SetSimulatePhysics(true);
	RootComponent = VisualMesh;
}


// Called when the game starts or when spawned
void APickable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


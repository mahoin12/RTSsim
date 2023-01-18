// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include <Components/SceneComponent.h>
#include <Components/StaticMeshComponent.h>
#include "Components/BoxComponent.h"

// Sets default values
ATile::ATile()
{
    // Create the Root Component
    RootComponent = CreateAbstractDefaultSubobject<USceneComponent>(TEXT("RootComp"));
    // Create the Static Mesh Momponent
    TileMesh = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("TileMesh"));
    // Attaching Static Mesh Component to Root Component
    TileMesh->SetupAttachment(RootComponent);
    // Create Box Component to represent collision
    Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Mesh"));
    // Attaching Box Component to Root Component
    Collision->SetupAttachment(RootComponent);
    Collision->SetBoxExtent(FVector(50.f,50.f,10.f));
    Collision->SetCollisionProfileName("BlockAll");
}


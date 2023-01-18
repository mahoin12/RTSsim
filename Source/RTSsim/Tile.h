// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"


class UStaticMeshComponent;

UENUM()
enum class ETileType : uint8
{
	INVALID,
	GRASS,
	WATER,
	MAX UMETA(Hidden)

};



UCLASS()
class RTSSIM_API ATile : public AActor
{
	GENERATED_BODY()


public:
	// To represent tile index
	UPROPERTY(VisibleInstanceOnly, Category = "Tile")
		FIntPoint TileIndex;

	// Box Component to represent collision
	UPROPERTY(VisibleInstanceOnly, Category = "Tile")
		class UBoxComponent* Collision;

protected:
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Tile")
		ETileType TileType;

	// Static mesh to represent the pickup in the level
	UPROPERTY(EditDefaultsOnly, BluePrintReadWrite, Category = "Tile")
		UStaticMeshComponent* TileMesh;


public:
	// Sets default values for this actor's properties
	ATile();

};

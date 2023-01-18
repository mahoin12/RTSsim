// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridManager.generated.h"

class ATile;
UCLASS()
class RTSSIM_API AGridManager : public AActor
{
	GENERATED_BODY()


protected:
	// Defining number of tiles to creating grid width
	UPROPERTY(EditAnywhere, Category = "Grid|Layout")
		int32 GridWidth;
	// Defining number of tiles to creating grid height
	UPROPERTY(EditAnywhere, Category = "Grid|Layout")
		int32 GridHeight;
	// Distance between tiles
	UPROPERTY(EditAnywhere, Category = "Grid|Layout")
		float TileOffset;
	// The tile to spawn
	UPROPERTY(EditAnywhere, Category = "Grid|Setup")
		TSubclassOf<ATile> GrassTile;
	// The tile to spawn
	UPROPERTY(EditAnywhere, Category = "Grid|Setup")
		TSubclassOf<ATile> WaterTile;

public:
	// Sets default values for this actor's properties
	AGridManager();
	// 2D array for Tile class referances
	TArray<TArray<ATile*>> Grid2DArray;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};

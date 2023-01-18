// Fill out your copyright notice in the Description page of Project Settings.


#include "GridManager.h"
#include "Tile.h"

// Sets default values
AGridManager::AGridManager()
{


}


// Called when the game starts or when spawned
void AGridManager::BeginPlay()
{
	Super::BeginPlay();

	// Creating 2D array with zeroed
	Grid2DArray.SetNumZeroed(GridWidth);
	for (int32 i = 0; i < Grid2DArray.Num(); i++)
	{
		Grid2DArray[i].SetNumZeroed(GridHeight);
	}

	// Basing for 2D array creating tiles
	for (int32 y = 0; y < GridHeight; y++)
	{
		for (int32 x = 0; x < GridWidth; x++)
		{
			const float xPos = x * TileOffset;
			const float yPos = y * TileOffset;

			//Defining which sub class to should be spawned
			TSubclassOf<ATile> tileToSpawn = GrassTile;
			if ((x + y) % 2 == 1)
			{
				tileToSpawn = WaterTile;
			}
			// Spawning tiles
			ATile* newTile = GetWorld()->SpawnActor<ATile>(tileToSpawn, FVector(FIntPoint(xPos, yPos)), FRotator::ZeroRotator);
			// Setting index for tiles
			newTile->TileIndex = FIntPoint(x, y);
			newTile->SetActorLabel(FString::Printf(TEXT("Tile_%d-%d"), x, y));
			// Storage information tiles
			Grid2DArray[x][y] = newTile;
		}
	}
}


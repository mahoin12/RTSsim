// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnManager.h"
#include "Soldier.h"
#include "Kismet/GameplayStatics.h"
#include "RTSGameInstance.h"
#include "Tile.h"

// Sets default values
ASpawnManager::ASpawnManager()
{

}

// Called when the game starts or when spawned
void ASpawnManager::BeginPlay()
{
	Super::BeginPlay();
		
		// Getting user defined number of soldiers from game instance
		URTSGameInstance* GI = Cast<URTSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		if(GI)
		{
			NumberOfSoldiers = GI->number;
		}

		// Set the spawn parameters
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		// Check for a valid World
		UWorld* World = GetWorld();
		// Setting for TileArray to create zeroed numbers with desired width
		SoldierArray.SetNumZeroed(NumberOfSoldiers);
		if (World)
		{
			// To spawn as many soldiers as the number of soldiers
			for (int32 i = 0; i < NumberOfSoldiers; i++)
			{
				GrupNumber = int32(i / 10);
				// Calculate to spawn location
				int32 PosX = ((GrupNumber/2) * 101) + ((i % 10) * 6)+60;
				int32 PosY;
				if (i % 2 == 0) 
				{
					PosY = ((GrupNumber) % 2 * 101) + 121;
				}
				else
				{
					PosY = ((GrupNumber) % 2 * 101)+ 101;
				}
				// Spawn the soldier to defined location
				ASoldier* newSoldier = GetWorld()->SpawnActor<ASoldier>(Soldier, FVector(PosY, PosX, 50), FRotator::ZeroRotator, Params);
				if (newSoldier)
				{
					// Setting index for each soldiers group
					newSoldier->SoldierIndex= GrupNumber;
					// To store soldier reference
					SoldierArray[i] = newSoldier;
					// Giving default controller to each created soldier
					newSoldier->SpawnDefaultController();
				}
			}
			// Setting for TileArray to create zeroed numbers with desired width
			TileArray.SetNumZeroed(GrupNumber + 1);
			for (int32 i = 0; i< GrupNumber+1; i++)
			{
				int32 PosY = (i % 2) * 101;
				int32 PosX = (i / 2)*101;
				// Spawn the symbol to defined location
				ATile* newTile = GetWorld()->SpawnActor<ATile>(Tile_Symbol, FVector(PosY, PosX, 40), FRotator::ZeroRotator);
				if(newTile)
				{
					// To store symbol reference
					TileArray[i] = newTile;
				}
			}
		}
}
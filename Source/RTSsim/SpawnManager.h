// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnManager.generated.h"

class ASoldier;
class ATile;

UCLASS()
class RTSSIM_API ASpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnManager();

	int32 GrupNumber;

	// The number of the to spawn soldiers
	int32 NumberOfSoldiers;
	// To store soldier reference
	TArray<ATile*> TileArray;
	//  To store symbol reference
	TArray<ASoldier*> SoldierArray;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// The soldier to spawn
	UPROPERTY(EditAnywhere, Category = "Soldier|Setup")
		TSubclassOf<ASoldier> Soldier;
	// The symbol to spawn
	UPROPERTY(EditAnywhere, Category = "Grid|Setup")
		TSubclassOf<ATile> Tile_Symbol;
};

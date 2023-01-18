// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "GameFramework/Pawn.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "UObject/UObjectGlobals.h"
#include "FindRandomLocation.generated.h"

/**
 * 
 */
class AGridManager;
class ASpawnManager;
class ATile;
UCLASS(Blueprintable)
class RTSSIM_API UFindRandomLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:

	UFindRandomLocation(FObjectInitializer const& object_initializer);

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory);

protected:

	// Define GridManager reference
	AGridManager* GridManagerRef;
	// Define SpawnManager reference
	ASpawnManager* SpawnManagerRef;
	// Array to 2D mapping
	TArray<TArray<int32>> Int2DArray;
	// Variables
	int32 NumberOfSoldiers;

	int32 NumberOfGroups;

	int32 SoldierIndexRef;

	bool StartLoc = false;
};

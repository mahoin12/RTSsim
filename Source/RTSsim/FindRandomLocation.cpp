// Fill out your copyright notice in the Description page of Project Settings.


#include "FindRandomLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "RTSAIController.h"
//#include "BehaviorTree/Blackboard/BlackboadKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "blackboard_keys.h"
#include "GridManager.h"
#include "Tile.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "Soldier.h"
#include "RTSGameInstance.h"
#include "SpawnManager.h"

UFindRandomLocation::UFindRandomLocation(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Find Random Location");
	// Getting number of soldiers via Game Instance
	URTSGameInstance* GI = Cast<URTSGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	// Check avaible Game Instance reference then set value of number of soldiers to NumberOfSoldiers
	if (GI)
	{
		NumberOfSoldiers = GI->number;
	}
	// Creating 2D array with desired size
	NumberOfGroups = NumberOfSoldiers / 10;
	Int2DArray.SetNumZeroed(NumberOfGroups);
	for (int32 i = 0; i < Int2DArray.Num(); i++)
	{
		Int2DArray[i].SetNumZeroed(3);

	}
	// Fill random location in to Array
	for (int32 i = 0; i < Int2DArray.Num(); i++)
	{
		Int2DArray[i][0] = FMath::RandRange(0, 49);
		Int2DArray[i][1] = FMath::RandRange(0, 49);
	}
}
// Every soldier calling this function via behavior tree
EBTNodeResult::Type UFindRandomLocation::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	// Get AI controller
	auto const cont = Cast<ARTSAIController>(owner_comp.GetOwner());
	// For once time, at start send symbols to first destined location
	if (!StartLoc) {
		for (int32 i = 0; i < NumberOfGroups; i++)
		{
			SpawnManagerRef = Cast<ASpawnManager>(UGameplayStatics::GetActorOfClass(this, ASpawnManager::StaticClass()));
			if (SpawnManagerRef)
			{
				auto const TileShouldGo = SpawnManagerRef->TileArray[i];
				int32 PosX = Int2DArray[i][0] * 101;
				int32 PosY = Int2DArray[i][1] * 101;
				TileShouldGo->SetActorLocation(FVector(PosX, PosY, 40));
			}
		}
		StartLoc = true;
	}
	// Get Sodier reference which currently using behavior tree
	ASoldier* SoldierRef = Cast<ASoldier>(cont->GetPawn());
	// Get SoldierIndex reference from Soldier reference
	SoldierIndexRef = SoldierRef->SoldierIndex;
	FVector TilePos;
	// Considering delay and stuck when count hit 11 then define new location
	if (Int2DArray[SoldierIndexRef][2] == 11)
	{
		Int2DArray[SoldierIndexRef][0] = FMath::RandRange(0, 49);
		Int2DArray[SoldierIndexRef][1] = FMath::RandRange(0, 49);
		Int2DArray[SoldierIndexRef][2] = 0;
		// Send symbol to new location
		SpawnManagerRef = Cast<ASpawnManager>(UGameplayStatics::GetActorOfClass(this, ASpawnManager::StaticClass()));
		if (SpawnManagerRef)
		{
			auto const TileShouldGo = SpawnManagerRef->TileArray[SoldierIndexRef];
			int32 PosX = Int2DArray[SoldierIndexRef][0] * 101;
			int32 PosY = Int2DArray[SoldierIndexRef][1] * 101;
			TileShouldGo->SetActorLocation(FVector(PosX, PosY, 40));
		}
	}
	// Count when a soldier call behavior tree
	Int2DArray[SoldierIndexRef][2]++;
	// To get 2D array which storage tile reference we need access GridManager reference
	GridManagerRef = Cast<AGridManager>(UGameplayStatics::GetActorOfClass(this, AGridManager::StaticClass()));
	// Chech for available GridManager reference
	if (GridManagerRef)
	{
		// Calculate destined location
		int32 PosX = Int2DArray[SoldierIndexRef][0];
		int32 PosY = Int2DArray[SoldierIndexRef][1];
		auto const TileToGo = GridManagerRef->Grid2DArray[PosX][PosY];
		FIntPoint asd = TileToGo->TileIndex;
		TilePos = TileToGo->GetActorLocation();
	}
	// Send vector location to blackboard
	cont->get_blackboard()->SetValueAsVector(bb_keys::target_location, TilePos);
	// Finish with success
	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}